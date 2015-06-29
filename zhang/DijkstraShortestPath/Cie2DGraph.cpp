#include "Cie2DGraph.h"				//holds all function prototypes.

/*==============================================================================*
 * Function Bodies for startup/shutdown                                         *
 *==============================================================================*/

//------------------------------------------------------------------------------
// InitGraphics()
// InitGraphics2(width, height, x, y)
//
//  Do all initialization and setup needed to use this 'introductory graphics'
//  library, and open a width x height window at x,y on the screen.

void Cie2DGraph::InitGraphics()
{
  InitGraphics2("NWSUAF CIE 2D GRAPHICS Window",
                NU_SCREENWIDTH, NU_SCREENHEIGHT,
                NU_SCREEN_XPOS, NU_SCREEN_YPOS);
}

void Cie2DGraph::InitGraphics2(const char * title, int w, int h, int x, int y)
{
  // needed dummy main() arguments
    char *fakeArgs[] = { "dummy", 0 };
    int fakeArgc = 1;
    glutInit(&fakeArgc, fakeArgs);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
									// double buffering, use full 32-bit color
	glutInitWindowPosition(x, y);
	glutInitWindowSize(w, h);

	glutCreateWindow(title);
									// Open a window (Microsoft Windows)
	glClearColor(1.0,1.0,1.0,1.0);	// Set the background color
	glColor3d(0.0,0.0,0.0);			// Set the default 'drawing pen' color
	glPointSize(3.0);				// Set the line width.

	glMatrixMode(GL_PROJECTION);	// Select world-to-camera transform:
	glLoadIdentity();				// initialize it, then set
	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
	// left, right,bottom top;
									// an orthographic camera matrix; treats
									// glVertex() values as pixel measurements.
	glutDisplayFunc(DisplayCallback);		// Register the fcn. GLUT calls for drawing
	glutKeyboardFunc(KeyboardCallback);	// Register the fcn. GLUT calls for keystrokes

    glutReshapeFunc(ReshapeCallback);
    glutVisibilityFunc(VisibilityCallback);
	glutIdleFunc(IdleCallback);

	app_visible = 1;
	app_time = glutGet(GLUT_ELAPSED_TIME);

	glutMainLoop();
}

void Cie2DGraph::IdleCallback(void)
{
	glutPostRedisplay();
}

void Cie2DGraph::ReshapeCallback(int w, int h)
{
	glViewport(0, 0, w, h);
	//glutPostRedisplay();
}

void Cie2DGraph::VisibilityCallback (int visibility)
{
  app_visible = visibility == GLUT_VISIBLE;
}

//------------------------------------------------------------------------------
// DisplayCallback()
//
// Called repeatedly to update the display. Calls user's myDisplay()
// every NU_PAUSE milliseconds.

void Cie2DGraph::DisplayCallback()
{
	int now = glutGet(GLUT_ELAPSED_TIME);
	if (app_visible && (now - app_time) > NU_PAUSE) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        display();
		glutSwapBuffers();
		app_time = now;
	}
}

//------------------------------------------------------------------------------
// KeyboardCallback(key, x, y)
//
// Called when users press a key. Just calls user's myKeyboard().

void Cie2DGraph::KeyboardCallback(unsigned char key, int x, int y)
{
    keyboard(key, x, glutGet(GLUT_WINDOW_HEIGHT) - y);
    glutPostRedisplay();
}


/*==============================================================================*
 *		Function Bodies for on-screen drawing and animation                     *
 *==============================================================================*/


//------------------------------------------------------------------------------
// SetPenColor(red, green, blue)
// SetPenColorHex(color)

void Cie2DGraph::SetPenColor(double red, double green, double blue)
{
	glColor3d(red,green,blue);
}


void Cie2DGraph::SetPenColorHex(unsigned long color)
{
     SetPenColor((color >> 16) / 256.0,
                 (color >> 8 & 0xFF) / 256.0,
                 (color & 0xFF) / 256.0);
}

//------------------------------------------------------------------------------
// DrawLine(x0, y0, x1, y1)
//
// Draw a line from (x0,y0) and ending at (x1,y1).
// (doesn't use relative addressing).
// x,y are measured in pixels.

void Cie2DGraph::DrawLine(double x0, double y0, double x1, double y1)
{
	glBegin(GL_LINES);				// Draw lines between pairs of points.
	glVertex2d(x0,y0);				// first line: begins at this point,
	glVertex2d(x1,y1);				// ends at this point.
	glEnd();						// No more pairs of points to draw.
	glFlush();						// Finish any pending drawing commands.
}

void Cie2DGraph::DrawArrowLine(double x0, double y0, double x1, double y1, double s1, double s2)
{
    double r=5, l, t;
    double k;
    double xe, ye, xk, yk, xp, yp, xq, yq;

    l = sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
    if(l<1.0e-6) return;

    t = (l-s1)/l;
    xe = x0 + t*(x1-x0);
    ye = y0 + t*(y1-y0);

    t = (l-s1-s2)/l;
    xk = x0 + t*(x1-x0);
    yk = y0 + t*(y1-y0);

    if(abs(y1-y0)<1.0e-6)
    {
        xp = xk; yp = y0+r;
        xq = xk; yq = y0-r;
    }
    else
    {
       k = -(x1-x0)/(y1-y0);
       xp = xk + r/sqrt(1+k*k); yp = yk + r*k/sqrt(1+k*k);
       xq = xk - r/sqrt(1+k*k); yq = yk - r*k/sqrt(1+k*k);
    }

	glBegin(GL_LINES);				// Draw lines between pairs of points.
	glVertex2d(x0,y0);				// first line: begins at this point,
	glVertex2d(x1,y1);				// ends at this point.
	glEnd();						// No more pairs of points to draw.

	DrawFillTriangle(xe, ye, xp, yp, xq, yq);
	glFlush();						// Finish any pending drawing commands.
}


//-----------------------------------------------------------------------------
// DrawBox (x0, y0, x1, y1)
//
// Draw a box using the current pen color with lower left corner at (x0,y0)
// and upper right corner at x1, y1.
// x,y are measured in pixels.

void Cie2DGraph::DrawBox(double x0, double y0, double x1, double y1)
{
	glBegin(GL_LINE_STRIP);			// Draw a connected line from
	glVertex2d(x0,y0);				// corner to
	glVertex2d(x1,y0);				// corner to
	glVertex2d(x1,y1);				// corner to
	glVertex2d(x0,y1);				// corner to
	glVertex2d(x0,y0);				// corner,
	glEnd();						// then stop--we're finished.
	glFlush();						// Finish any pending drawing commands.
}


//------------------------------------------------------------------------------
// DrawFillBox (x0, y0, x1, y1)
//
// Draw a box and fill the region inside it using the current pen color.
// You can specify the pen color with the SetPenColor() function.
// The default color is black.
// x,y are measured in pixels.

void Cie2DGraph::DrawFillBox(double x0, double y0, double x1, double y1)

{
	glBegin(GL_TRIANGLES);			// Draw a connected line from
        glTexCoord2d(0,0);
        glVertex2d(x0,y0);				// corner to
        glTexCoord2d(1,0);
        glVertex2d(x1,y0);				// lcorner to
        glTexCoord2d(0,1);
        glVertex2d(x0,y1);				// corner to

        glTexCoord2d(1,0);
        glVertex2d(x1,y0);				// lcorner to
        glTexCoord2d(1,1);
        glVertex2d(x1,y1);				// corner to
        glTexCoord2d(0,1);
        glVertex2d(x0,y1);				// corner to
	glEnd();						// then stop--we're finished.
	//glFlush();						// Finish any pending drawing commands.
}

void Cie2DGraph::DrawTriangle(double x0, double y0, double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINE_LOOP);			// Draw a connected line from
	glVertex2d(x0,y0);				// Vertex 0
	glVertex2d(x1,y1);				// Vertex 1
	glVertex2d(x2,y2);				// Vertex 2
	glVertex2d(x0,y0);				// corner,
	glEnd();						// then stop--we're finished.
	glFlush();						// Finish any pending drawing commands.
}

//------------------------------------------------------------------------------
// DrawFillTriangle(x0, y0, x1, y1, x2, y2)
//
// Draw a triangle and fill the region inside it using the current pen color
// Default fill color is black, but you can change it with the SetPenColor() function.
// x,y are measured in pixels.

void Cie2DGraph::DrawFillTriangle(double x0, double y0, double x1, double y1, double x2, double y2)

{
	glBegin(GL_POLYGON);			// Draw a connected line from
	glVertex2d(x0,y0);				// Vertex 0
	glVertex2d(x1,y1);				// Vertex 1
	glVertex2d(x2,y2);				// Vertex 2
	glVertex2d(x0,y0);				// corner,
	glEnd();						// then stop--we're finished.
	glFlush();						// Finish any pending drawing commands.
}


//-----------------------------------------------------------------------------
// DrawCircle(xctr, yctr, radius)
//
// Draw the outline of a circle centered at (xctr,yctr) and width of 'radius'.
// using the current pen color and line width. Default pen color is black, but
// the 'SetPenColor()' function can change it.
// Draws the circle as a sequence of very short,straight lines.
// x,y, radius are measured in pixels.

void Cie2DGraph::DrawCircle(double xctr, double yctr, double radius)
{
	double vectorX,vectorY;			// vector to a point on circle from its center
	double angle;					// Angle in radians from circle start point.

	glBegin(GL_LINE_STRIP);		// Tell OpenGL to draw a series of lines:
	for(angle=0; angle < 2.0*M_PI + NU_ANGLESTEP; angle+= NU_ANGLESTEP)
	{								// (>2PI so that circle is always closed)
		vectorX= xctr + radius * cos(angle);	// set line endpoint
		vectorY= yctr + radius * sin(angle);
		glVertex2d(vectorX,vectorY);	// plot the line endpoint.
	}
	glEnd();						// finished drawing line segments.
	glFlush();						// Finish any pending drawing commands
}

//----------------------------------------------------------------------------
// DrawFillCircle(xctr, yctr, radius)
//
// Draw a circle and fill the region inside it using the the current pen color.
// Default pen color is black, but the SetFillColor() function will change it.
// Draws the shape using filled triangles.
// x,y, radius are measured in pixels

void Cie2DGraph::DrawFillCircle(double xctr, double yctr, double radius)
{
	double vectorX1,vectorY1;		// vector to a point on circle from its center
	double vectorX0,vectorY0;		// previous version of vectorX1,Y1;
	double angle;					// Angle in radians from circle start point.

	glBegin(GL_TRIANGLES);		// Tell OpenGL to draw a series of triangles
	vectorX1 = xctr + radius;	// Start at the circle's rightmost point.
	vectorY1 = yctr;
	for(angle=NU_ANGLESTEP;		// step through all other points on circle;
		angle < 2.0*M_PI + NU_ANGLESTEP; angle+= NU_ANGLESTEP)
	{								// (>2PI so that circle is always closed)
		vectorX0 = vectorX1;		// save previous point's position,
		vectorY0 = vectorY1;
		vectorX1= xctr + radius*cos(angle);	// find a new point on the circle,
		vectorY1= yctr + radius*sin(angle);
		glVertex2d(xctr,yctr);		// plot the points of a triangle (CCW order)
		glVertex2d(vectorX0,vectorY0);	// center-->old pt-->new pt.
		glVertex2d(vectorX1,vectorY1);
	}
	glEnd();						// finished drawing triangles.
	glFlush();						// Finish any pending drawing commands
}

void Cie2DGraph::DrawEllipse(double xctr, double yctr, double x_radius, double y_radius)
{
	double vectorX, vectorY;			// vector to a point on circle from its center
	double angle;					// Angle in radians from circle start point.

	glBegin(GL_LINE_STRIP);		// Tell OpenGL to draw a series of lines:
	for(angle=0; angle < 2.0*M_PI + NU_ANGLESTEP; angle+= NU_ANGLESTEP)
	{								// (>2PI so that circle is always closed)
		vectorX= xctr + x_radius * cos(angle);	// set line endpoint
		vectorY= yctr + y_radius * sin(angle);
		glVertex2d(vectorX, vectorY);	// plot the line endpoint.
	}
	glEnd();						// finished drawing line segments.
	glFlush();						// Finish any pending drawing commands
}

void Cie2DGraph::DrawDonet(double xctr, double yctr, double x_radius, double y_radius, double ratio)
{
	double vectorX, vectorY;			// vector to a point on circle from its center
	double angle;					// Angle in radians from circle start point.

	glBegin(GL_LINE_STRIP);		// Tell OpenGL to draw a series of lines:
	for(angle=0; angle < 2.0*M_PI + NU_ANGLESTEP; angle+= NU_ANGLESTEP)
	{								// (>2PI so that circle is always closed)
		vectorX= xctr + x_radius * cos(angle);	// set line endpoint
		vectorY= yctr + y_radius * sin(angle);
		glVertex2d(vectorX, vectorY);	// plot the line endpoint.
	}
	glEnd();						// finished drawing line segments.

	glBegin(GL_LINE_STRIP);		// Tell OpenGL to draw a series of lines:
	for(angle=0; angle < 2.0*M_PI + NU_ANGLESTEP; angle+= NU_ANGLESTEP)
	{								// (>2PI so that circle is always closed)
		vectorX= xctr + ratio*x_radius * cos(angle);	// set line endpoint
		vectorY= yctr + ratio*y_radius * sin(angle);
		glVertex2d(vectorX, vectorY);	// plot the line endpoint.
	}
	glEnd();						// finished drawing line segments.

	glFlush();						// Finish any pending drawing commands
}

void Cie2DGraph::DrawFillEllipse(double xctr, double yctr, double x_radius, double y_radius)
{
	double vectorX1,vectorY1;		// vector to a point on circle from its center
	double vectorX0,vectorY0;		// previous version of vectorX1,Y1;
	double angle;					// Angle in radians from circle start point.

	glBegin(GL_TRIANGLES);		// Tell OpenGL to draw a series of triangles
	vectorX1 = xctr + x_radius;	// Start at the circle's rightmost point.
	vectorY1 = yctr;
	for(angle=NU_ANGLESTEP;		// step through all other points on circle;
		angle < 2.0*M_PI + NU_ANGLESTEP; angle+= NU_ANGLESTEP)
	{								// (>2PI so that circle is always closed)
		vectorX0 = vectorX1;		// save previous point's position,
		vectorY0 = vectorY1;
		vectorX1= xctr + x_radius*cos(angle);	// find a new point on the circle,
		vectorY1= yctr + y_radius*sin(angle);
		glVertex2d(xctr, yctr);		// plot the points of a triangle (CCW order)
		glVertex2d(vectorX0,vectorY0);	// center-->old pt-->new pt.
		glVertex2d(vectorX1,vectorY1);
	}
	glEnd();						// finished drawing triangles.
	glFlush();						// Finish any pending drawing commands
}

void Cie2DGraph::DrawFillDonet(double xctr, double yctr, double x_radius, double y_radius, double ratio)
{
	double vectorX3,vectorY3;		// vector to a point on circle from its center
	double vectorX2,vectorY2;		// vector to a point on circle from its center
	double vectorX1,vectorY1;		// vector to a point on circle from its center
	double vectorX0,vectorY0;		// previous version of vectorX1,Y1;
	double angle;					// Angle in radians from circle start point.

	glBegin(GL_TRIANGLES);		// Tell OpenGL to draw a series of triangles
	vectorX1 = xctr + x_radius;	// Start at the circle's rightmost point.
	vectorY1 = yctr;
	vectorX3 = xctr + ratio*x_radius;	// Start at the circle's rightmost point.
	vectorY3 = yctr;
	for(angle=NU_ANGLESTEP;		// step through all other points on circle;
		angle < 2.0*M_PI + NU_ANGLESTEP; angle+= NU_ANGLESTEP)
	{								// (>2PI so that circle is always closed)
		vectorX0 = vectorX1;		// save previous point's position,
		vectorY0 = vectorY1;
		vectorX2 = vectorX3;		// save previous point's position,
		vectorY2 = vectorY3;
		vectorX1= xctr + x_radius*cos(angle);	// find a new point on the circle,
		vectorY1= yctr + y_radius*sin(angle);
		vectorX3= xctr + ratio*x_radius*cos(angle);	// find a new point on the circle,
		vectorY3= yctr + ratio*y_radius*sin(angle);

		glVertex2d(vectorX2, vectorY2);		// plot the points of a triangle (CCW order)
		glVertex2d(vectorX0,vectorY0);	// center-->old pt-->new pt.
		glVertex2d(vectorX1,vectorY1);

		glVertex2d(vectorX1, vectorY1);		// plot the points of a triangle (CCW order)
		glVertex2d(vectorX3,vectorY3);	// center-->old pt-->new pt.
		glVertex2d(vectorX2,vectorY2);
    }
	glEnd();						// finished drawing triangles.
	glFlush();						// Finish any pending drawing commands
}

//-----------------------------------------------------------------------------
// DrawArc (xctr, yctr, radius, startAngle, endAngle)
//
// Draw a circular arc using the current pen color. Plots a portion of the
// circle whose center is (xctr,yctr) and width is given by 'radius', but only
// draws the portion of the circle between 'startAngle' and 'endAngle'.  Both
// the start and end angles are measured from the right-most point on the circle
// (e.g. the x-axis intercept for a circle centered at the origin) in the
// counter-clockwise direction, in degrees.  Default pen color is black, but
// the 'SetPenColor()' function can change it for you.
// Draws the arc as a sequence of short, straight-line segments.
// x,y, radius are measured in pixels
// Angles are measured in degrees

void Cie2DGraph::DrawArc (double xctr, double yctr, double radius, double startAngle, double endAngle)
{
	double vectorX,vectorY;			// vector to a point on circle from its center
	double angle, ang0,ang1;

	ang0 = startAngle * (M_PI/180.0);	// convert degrees to radians
	ang1 = endAngle * (M_PI/180.0);
	glBegin(GL_LINE_STRIP);		// tell OpenGL to draw connected lines.
	for(angle=ang0; angle <= ang1+NU_ANGLESTEP; angle+= NU_ANGLESTEP)
		{
			vectorX = xctr + radius*cos(angle);	// find a line endpoint
			vectorY = yctr + radius*sin(angle);
			glVertex2d(vectorX,vectorY);	// plot that line endpoint,
		}
	glEnd();						// Finished drawing connected lines.
	glFlush();						// Finish any pending drawing commands
}


//-----------------------------------------------------------------------------
// DrawPieArc (xctr, yctr, radius, startAngle, endAngle)
//
// Draw a circular arc and fill the pie-slice-shaped region between the arc
// and its center point with the current pen color.  Default fill color is black,
// but the SetFillColor() function can change it.
// Draws the shape using filled triangles.
// x,y, radius are measured in pixels
// Angles are measured in degrees

void Cie2DGraph::DrawPieArc(double xctr, double yctr, double radius, double startAngle, double endAngle)
{
	double vectorX1,vectorY1;		// vector to a point on circle from its center
	double vectorX0,vectorY0;		// previous version of vectorX1,Y1;
	double angle,ang0,ang1;			// Angle in radians from circle start point.

	ang0 = startAngle * (M_PI/180.0);	// convert degrees to radians
	ang1 = endAngle * (M_PI/180.0);
	glBegin(GL_TRIANGLES);		// Tell OpenGL to draw a series of triangles
								// Start at the circle's rightmost point.
	vectorX1 = xctr + radius*cos(ang0);
	vectorY1 = yctr + radius*sin(ang0);
	for(angle=ang0 + NU_ANGLESTEP;// step through all other points on circle;
		angle < ang1 + NU_ANGLESTEP; angle += NU_ANGLESTEP)
	{								// (add to ang1 to ensure arcs can close)
		vectorX0 = vectorX1;		// save previous point's position,
		vectorY0 = vectorY1;
		vectorX1= xctr + radius*cos(angle);	// find a new point on the circle,
		vectorY1= yctr + radius*sin(angle);
		glVertex2d(xctr,yctr);		// plot the points of a triangle (CCW order)
		glVertex2d(vectorX0,vectorY0);	// center-->old pt-->new pt.
		glVertex2d(vectorX1,vectorY1);
	}
	glEnd();						// finished drawing triangles.
	glFlush();						// Finish any pending drawing commands


	vectorY1=yctr;					// Set starting point
	vectorX1=xctr;
}


//-----------------------------------------------------------------------------
// DrawText2D(font, x0, y0, pString)
//
//  Write the text string stored at 'pString' to the display screen using the
//  current pen color and the specified font.
//  It places the lower left corner of the first line of text
//  at position x0,y0.
//	Example:  DrawText2D(TIMES_ROMAN, 10,20,"Hello!");
//
// Available fonts:
// rom10 (TIMES_ROMAN size 10)
// rom24 (TIMES_ROMAN size 24)
// helv10 (HELVETICA size 10)
// helv12 (HELVETICA size 12)
// helv18 (HELVETICA size 18)

void Cie2DGraph::DrawText2D(void * font, double x0, double y0, const char* pString)
{
	int i, imax;							// counter for characters.
	int		lines;							// counter for each 'newline' char.

	lines = 0;
	glRasterPos2d(x0, y0);			// set text's lower-left corner position
	imax = 1000;						// limit the number of chars we print.
	for(i=0; pString[i] != '\0'; i++)		// for each char,
	{
		if (pString[i] == '\n')						// is it a new-line?
		{
			lines++;								// count it, and
			glRasterPos2d(x0, y0-(lines * 18.0));	// move down to next line
		}
		glutBitmapCharacter(font, pString[i]);
	}
}


//------------------------------------------------------------------------------
// GetWindowHeight()
// GetWindowWidth()
//
// Return window height and width in pixels.

int Cie2DGraph::GetWindowHeight() { return glutGet(GLUT_WINDOW_HEIGHT); }
int Cie2DGraph::GetWindowWidth() { return glutGet(GLUT_WINDOW_WIDTH); }


//----------------------------------------------------------------------------
// SetDottedLines()
//
//  Change pen to draw dotted lines instead of solid lines. All lines drawn
//  after this call will be drawn dotted until you call the 'DrawSolidLines()'
//  function.

void Cie2DGraph::SetDottedLines(void)
{
	glLineStipple(4, 0xAAAA);		// Set OpenGL's fill pattern bits,
	glEnable(GL_LINE_STIPPLE);		// enable it,
	glFlush();						// and finish any pending drawing commands
}


//-----------------------------------------------------------------------------
// SetSolidLines()
//
//  Change the pen back to the default of drawing solid lines.  All lines drawn
//  after this call will be drawn solid until you call the 'DrawDottedLines()'
//  function.

void Cie2DGraph::SetSolidLines(void)
{
	glDisable(GL_LINE_STIPPLE);		// disable the fill pattern
	glFlush();
}


//-----------------------------------------------------------------------------
// SetLineWidth(wide)
//
//  Change the width (in pixels) of the lines drawn by the pen.  Default value is 3.0;
//  Careful! if you set 'wide' to zero, all lines drawn are invisible!

void Cie2DGraph::SetLineWidth(double wide)
{
	glLineWidth((GLfloat)wide);		// (cast to OpenGL's float type)
}


//-----------------------------------------------------------------------------
// ClearWindow()
//
//  Calls OpenGL 'clear screen' function; fills the screen with background color.
//  You can change that by calling the SetBackgndColor() function

void Cie2DGraph::ClearWindow(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
}


//-----------------------------------------------------------------------------
// SetBackgndColor(red, green, blue)
// SetBackgndColorHex(color)
//
//  Sets the color used by 'ClearWindow()' function, and then fills the entire
// window with that color.

void Cie2DGraph::SetBackgndColor(double red, double green, double blue)
{
		glClearColor(red, green, blue, 0.0);	// Set the background color
		glClear(GL_COLOR_BUFFER_BIT);			// Clear window using that color
}

void Cie2DGraph::SetBackgndColorHex(unsigned long color)
{
    SetBackgndColor((color >> 16) / 256.0,
                    (color >> 8 & 255) / 256.0,
                    (color & 255) / 256.0);
}

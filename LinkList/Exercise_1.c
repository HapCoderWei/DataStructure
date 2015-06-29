typedef struct City {
    char name;
    int x;
    int y;
} City, *Head;

/* (1) */
int *Location(Head L; char name) {
    City *p;
    int a[2] = {-1, -1};
    p = L->next;

    while(p->name != name && p != NULL) {
        p = p->next;
    }
    if (!p) return a;
    else {
        a[0] = p->x;
        a[1] = p->y;
    }

    return a;
}

/*  (2)  */
char *Distance(Head L, int x, int y, int distance) {
    int range;
    char city[N] = {};  /* N is all the citys number */
    int counter = 0;
    City *p;
    p = L->next;

    while(p != NULL) {
        range = CalculateDistance(x, y, p->x, p->y);
        if(range <= distance) {
            city[counter] = p->name;
        }
        p = p->next;
    }
    
    return city;
}
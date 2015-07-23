#include "dot.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int yardInSteps(int yard) {
    return -8*(yard/5) + 80;
}

Point *getPoint(Dot *dot) {
    Point *point = malloc(sizeof(Point));
    switch (dot->yref) {
        case fsideline:
            point->y = dot->ysteps;
            break;
        case bsideline:
            point->y = 84+dot->ysteps;
            break;
        case fhash:
            point->y = 28+dot->ysteps;
            break;
        case bhash:
            point->y = 56+dot->ysteps;
            break;
    }
    switch(dot->side) {
        case 1:
            point->x = (-1*yardInSteps(dot->yard))-dot->xsteps;
            break;
        case 2:
            point->x = yardInSteps(dot->yard)+dot->xsteps;
            break;
    }
    return point;
}

Dot *getDot(Point *point) {
    Dot *dot = malloc(sizeof(Dot));

    float xsteps = point->x*((point->x < 0)?-1:1);
    dot->yard = 50-(((int)(xsteps/8)+((fmod(xsteps, 8) > 4)?1:0))*5);

    if (point->x < 0) {
        dot->side = 1;
        dot->xsteps = -1*(point->x+(8*((50-dot->yard)/5)));
    }
    else {
        dot->side = 2;
        dot->xsteps = point->x-(8*((50-dot->yard)/5));
    }

    if (point->y < 14) {
        dot->yref = fsideline;
        dot->ysteps = point->y;
    }
    else if (point->y < 42) {
        dot->yref = fhash;
        dot->ysteps = point->y-28;
    }
    else if (point->y < 70) {
        dot->yref = bhash;
        dot->ysteps = point->y-56;
    }
    else {
        dot->yref = bsideline;
        dot->ysteps = point->y-84;
    }

    return dot;
}

Dot *midDot(Dot *one, Dot *two) {
    Point *pone = getPoint(one);
    Point *ptwo = getPoint(two);
    Point *pmid = midPoint(pone, ptwo);
    Dot *mid = getDot(pmid); 
    free(pone);
    free(ptwo);
    free(pmid);
    return mid;
}

Point *midPoint(Point *one, Point *two) {
    Point *mid = malloc(sizeof(Point));
    mid->x = (one->x+two->x)/2;
    mid->y = (one->y+two->y)/2;
    return mid;
}

void printDot(Dot *dot) {
    printf("Side %d: ", dot->side);
    if (dot->xsteps < 0) {
        printf("%.2f inside ", dot->xsteps*-1);
    }
    else if (dot->xsteps > 0) {
        printf("%.2f outside ", dot->xsteps);
    }
    else {
        printf("On ");
    }
    printf("the %d yardline\t", dot->yard);
    if (dot->ysteps < 0) {
        printf("%.2f steps in frnt of ", dot->ysteps*-1);
    }
    else if (dot->ysteps > 0) {
        printf("%.2f steps behind ", dot->ysteps);
    }
    else {
        printf("On ");
    }
    switch(dot->yref) {
        case fsideline:
            printf("front sideline");
            break;
        case fhash:
            printf("front hash");
            break;
        case bhash:
            printf("back hash");
            break;
        case bsideline:
            printf("back sideline");
            break;
    }
    printf("\n");
}

void uglyPrintDot(Dot *dot) {
    printf("%d ", dot->side);
    if (dot->xsteps < 0) {
        printf("%.2f in ", dot->xsteps*-1);
    }
    else {
        printf("%.2f out ", dot->xsteps);
    }
    printf("%d ", dot->yard);
    if (dot->ysteps < 0) {
        printf("%.2f front ", dot->ysteps*-1);
    }
    else {
        printf("%.2f back ", dot->ysteps);
    }
    switch(dot->yref) {
        case fsideline:
            printf("fs");
            break;
        case fhash:
            printf("fh");
            break;
        case bhash:
            printf("bh");
            break;
        case bsideline:
            printf("bs");
            break;
    }
    printf("\n");
}

void printPoint(Point *point) {
    printf("%.2f, %.2f\n", point->y, point->x);
}

double distanceDot(Dot *one, Dot *two) {
    Point *pone = getPoint(one);
    Point *ptwo = getPoint(two);
    double d = distancePoint(pone, ptwo);
    free(pone);
    free(ptwo);
    return d;
}

double distancePoint(Point *one, Point *two) {
    return sqrt(pow(one->x-two->x, 2)+pow(one->y-two->y, 2));
}

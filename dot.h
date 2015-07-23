//dot.h
//for mb dots

typedef struct {
    /* Simplistic structure
     * for dot data such that
     * On the front sideline, on the 50
     * is (0, 0). Side 1 is quadrant 2, 
     * Side 2 is quadrant 1.
     */
    double x;
    double y;
} Point;

typedef struct {
    /* Annoying structure for
     * the way dots are
     * actually written.
     */
    
    //enum for what the y value's reference point is
    enum {
        fsideline,
        bsideline,
        fhash,
        bhash
    } yref;
    //steps off reference. Negative implies in front of.
    double ysteps;

    short side;
    int yard;
    //steps off yardline. Negative implies TOWARDS 50
    double xsteps;

} Dot;

Point *getPoint(Dot *dot);
Dot *getDot(Point *point);
Dot *midDot(Dot *one, Dot *two);
Point *midPoint(Point *one, Point *two);
double distanceDot(Dot *one, Dot *two);
double distancePoint(Point *one, Point *two);

void printDot(Dot *dot);
void uglyPrintDot(Dot *dot);
void printPoint(Point *point);

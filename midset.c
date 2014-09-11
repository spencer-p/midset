#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "dot.h"

int parse(FILE *stream, Dot *dot) {
    char io[8], fb[16], yref[3];

    int r = fscanf(stream, "%hd %lf %s %d %lf %s %s\n", &dot->side, &dot->xsteps, io, &dot->yard, &dot->ysteps, fb, yref);
    if (r == EOF) {
        return 1;
    }
    else if (r != 7) {
        fprintf(stderr, "Formatting\n");
        fprintf(stderr, "%d %lf %s %d %lf %s %s\n", dot->side, dot->xsteps, io, dot->yard, dot->ysteps, fb, yref);
        return 2;
    }

    if (io[0] == 'i') {
        dot->xsteps *= -1;
    }
    if (fb[0] == 'f') {
        dot->ysteps *= -1;
    }
    if (strcmp(yref, "fs") == 0) {
        dot->yref = fsideline;
    }
    else if (strcmp(yref, "fh") == 0) {
        dot->yref = fhash;
    }
    else if (strcmp(yref, "bh") == 0) {
        dot->yref = bhash;
    }
    else {
        dot->yref = bsideline;
    }
    return 0;
}

void calc(Dot **dots, int count) {
    if (count <= 2) {
        return;
    }
    dots[count/2] = midDot(dots[0], dots[count-1]);
    calc(&dots[0], (count/2)+1);
    calc(&dots[count/2], (count/2)+1);
}

int main(int argc, char **argv) {

    bool ugly = false, setnumbers = false, all = false;
    int div = 3;
    int c;

    while ((c = getopt(argc, argv, "hud:na")) != -1) {
        switch (c) {
            case 'h':
                printf("%s [file]\n", argv[0]);
                printf("\tAccepts a file to read, otherwise stdin\n");
                printf("\t-u: ugly output\n");
                printf("\t-n: output set numbers\n");
                printf("\t-a: also print input sets\n");
                printf("\t-d [n]: division of sets (2, 4, 8...)\n");
                return 0;
                break;
            case 'u':
                ugly = true;
                break;
            case 'd':
                div = atoi(optarg)+1;
                if (fmod(log2(div-1), 1) != 0) {
                    fprintf(stderr, "Invalid breakdown, pls stop.\n");
                    return 1;
                }
                break;
            case 'n':
                setnumbers = true;
                break;
            case 'a':
                all = true;
                break;
        }

    }

    FILE *in = fopen(argv[optind], "r");
    if (in == NULL) {
        in = stdin;
    }

    Dot **dots = calloc(div, sizeof(Dot**));
    dots[div-1] = malloc(sizeof(Dot));
    parse(in, dots[div-1]);
    int set = 0;

    while (1) {

        //get rid of the first and move the next in its place
        free(dots[0]);
        dots[0] = dots[div-1];
        //print out the first dot
        if (all) {
            if (setnumbers) {
                printf("Set %d:\t\t", set);
            }
            if (ugly) {
                uglyPrintDot(dots[0]);
            }
            else {
                printDot(dots[0]);
            }
        }
        dots[div-1] = malloc(sizeof(Dot)); //make space for new one
        if (parse(in, dots[div-1])) { //read it in, if none exit loop
            break;
        }
        calc(dots, div); //calculate them all

        //print
        for (int i = 1; i < div-1; i++) {
            if (setnumbers) {
                printf("Set %d & %d/%d:\t", set, i, div-1);
            }
            if (ugly) {
                uglyPrintDot(dots[i]);
            }
            else {
                printDot(dots[i]);
            }
            free(dots[i]);
        }

        set++; //count the sets, duh
    }

    free(dots[0]);
    free(dots[div-1]);
    free(dots);
    fclose(in);
    return 0;
}

// Name: Ritabrata Das
// Roll No. : 20CS8002

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

// Defining structure for rectangle
typedef struct {
    float x, y, xlen, ylen;
} rectangle;

// Defining structure for rectangle with it's height
typedef struct {
    float y1, y2, h;
} rect_height;

// Defining structure for point
typedef struct {
    float x, y;
} point;

// Function to get the points required in Part 2
point *getPoints(rect_height *recs, int l, int r, int *size){
    int s1, s2, mid, s = 0, i = 0, j = 0;
    float hl = 0, hr = 0, h, hprev = 0;
    point *left, *right, *points;

    // If the left and right coordinates are the same
    if (l == r){
        point *points = (point *)malloc(sizeof(point) * 2);
        points[0].y = recs[l].y1;
        points[0].x = recs[l].h;
        points[1].y = recs[l].y2;
        points[1].x = 0;
        (*size) = 2;
        return points;
    }

    // Calculate the middle of left and right coordinates
    mid = (l + r) / 2;

    // Recursively storing the coordinates of the rectangles
    left = getPoints(recs, l, mid, &s1);
    right = getPoints(recs, mid + 1, r, &s2);

    points = (point *)malloc(0);

    // Loop to check the left side.
    while (i < s1 && j < s2){
        if (left[i].y < right[j].y){
            hl = left[i].x;
            h = (hl > hr) ? hl : hr;
            if (hprev != h){
                if (hprev != 0){
                    s++;
                    points = realloc(points, sizeof(point) * s);
                    points[s - 1].y = left[i].y;
                    points[s - 1].x = hprev;
                }
                s++;
                points = realloc(points, sizeof(point) * s);
                points[s - 1].y = left[i].y;
                points[s - 1].x = h;
            }
            i++;
        } else {
            hr = right[j].x;
            h = (hl > hr) ? hl : hr;
            if (hprev != h){
                if (hprev != 0){
                    s++;
                    points = realloc(points, sizeof(point) * s);
                    points[s - 1].y = right[j].y;
                    points[s - 1].x = hprev;
                }
                s++;
                points = realloc(points, sizeof(point) * s);
                points[s - 1].y = right[j].y;
                points[s - 1].x = h;
            }
            j++;
        }
        hprev = h;
    }
    
    // Loop to check the right side
    while (i < s1){
        h = left[i].x;
        if (hprev != h){
            if (hprev != 0){
                s++;
                points = realloc(points, sizeof(point) * s);
                points[s - 1].y = left[i].y;
                points[s - 1].x = hprev;
            }
            s++;
            points = realloc(points, sizeof(point) * s);
            points[s - 1].y = left[i].y;
            points[s - 1].x = h;
        }
        i++;
        hprev = h;
    }

    while (j < s2){
        h = right[j].x;
        if (hprev != h){
            if (hprev != 0){
                s++;
                points = realloc(points, sizeof(point) * s);
                points[s - 1].y = right[j].y;
                points[s - 1].x = hprev;
            }
            s++;
            points = realloc(points, sizeof(point) * s);
            points[s - 1].y = right[j].y;
            points[s - 1].x = h;
        }
        hprev = h;
        j++;
    }
    (*size) = s;
    free(left);
    free(right);
    return points;
}

// Compute the vertical line that passes through every rectangle.
float computeVerticalLine(rectangle *recs, int n){
    float x_min = recs[0].x, x_max = recs[0].x + recs[0].xlen;

    for (int i = 1; i < n; i++){
        x_min = (x_min < recs[i].x) ? x_min : recs[i].x;
        x_max = (x_max > recs[i].x + recs[i].xlen) ? x_max : recs[i].x + recs[i].xlen;
    }

    return (x_min + x_max) / 2;
}

// Returning the boundary points in O(n*log(n)) time complexity.
point *computeBoundary(rectangle *recs, int n, float mid){
    int i, sl, sr, s = 0;
    rect_height *recl, *recr;
    point *left, *right, *points;

    recl = (rect_height *)malloc(sizeof(rect_height) * n);
    recr = (rect_height *)malloc(sizeof(rect_height) * n);
    for (i = 0; i < n; i++){
        recl[i].y1 = recs[i].y;
        recr[i].y1 = recs[i].y;
        recl[i].y2 = recs[i].y + recs[i].ylen;
        recr[i].y2 = recs[i].y + recs[i].ylen;
        recl[i].h = mid - recs[i].x;
        recr[i].h = recs[i].x + recs[i].xlen - mid;
    }

    left = getPoints(recl, 0, n - 1, &sl);
    right = getPoints(recr, 0, n - 1, &sr);

    points = (point *)malloc(0);
    for (i = 0; i < sl; i++){
        if (left[i].x != 0){
            s++;
            points = realloc(points, sizeof(point) * s);
            points[s - 1].x = mid - left[i].x;
            points[s - 1].y = left[i].y;
        }
    }

    for (i = 0; i < sr; i++){
        if (right[i].x != 0){
            s++;
            points = realloc(points, sizeof(point) * s);
            points[s - 1].x = mid + right[i].x;
            points[s - 1].y = right[i].y;
        }
    }

    printf("\nBoundary: ");
    for (i = 0; i < s; i++){
        printf("(%.1f , %.1f)", points[i].x, points[i].y);
        if (i != s - 1){
            printf(" , ");
        }
    }
    printf("\n\n");
}

int main(){
    int n;
    float middle;

    // Inputting the number of rectangles
    printf("Write n: ");
    scanf(" %d", &n);

    // Dynamically storing the rectangles.
    rectangle * recs = (rectangle *)malloc(n * sizeof(rectangle));

    for (int i = 0; i < n; i++){
        scanf(" %f %f %f %f", &recs[i].x, &recs[i].y, &recs[i].xlen, &recs[i].ylen);
    }

    // Compute the middle vertical line.
    middle = computeVerticalLine(recs, n);
        
    // Computing the boundary in divide and conquer method.
    computeBoundary(recs, n, middle);

    return 0;
}
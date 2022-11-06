// Name: Ritabrata Das
// Roll No. : 20CS8002

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct containing an array of x and y coordinates, along with an integer partition to determine which half the point belongs.

typedef struct{
   long double coordinates[2];   
   int partition;
} Points;

// Function to display the array by linearly traversing
void displayArray(int arr[], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Quadratic time function to display the superiority index
void quadratic_time_algorithm(Points *point, int n){
    int* superiority_index = (int*)malloc(n * sizeof(int));

    // Applying normal bruteforce algorithm in O(n^2) algorithm.
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if((point[i].coordinates[0] > point[j].coordinates[0]) && (point[i].coordinates[1] > point[j].coordinates[1])){
                superiority_index[i]++;
            } 
        }
    }

    // Displaying the resultant array
    displayArray(superiority_index, n);

    // Deallocating the allocated space
    free(superiority_index);
}

// Merge Sort to sort the points according to the coordinates, i.e. either x or y coordinates
void merge_sort(Points * point, int n, int *arr, int coord){
    int i, j, a = 0, b = (n - 1) / 2, c = b + 1, d = n - 1, k = 0;
    
    if (n <= 1){
        return;
    }

    merge_sort(point, b - a + 1, arr, coord);
    merge_sort(point, d - c + 1, arr + (b - a + 1), coord);
    
    int *index = (int *)malloc(n * sizeof(int)); 
    i = a; 
    j = c;

    while ((i <= b) || (j <= d)) {
        if (i > b){
            index[k] = arr[j++];
        } else if (j > d){
            index[k] = arr[i++];
        } else if (point[arr[i]].coordinates[coord] < point[arr[j]].coordinates[coord]){
            index[k] = arr[i++];
        } else {
            index[k] = arr[j++];
        } 
        k++;
    }
    
    // Copying the indexes back to arr
    for (k = 0; k < n; ++k){
        arr[k] = index[k];
    } 

    // Deallocating the allocated space
    free(index);
}

// Recursive function to determine the index of the points based on their partition.
void recursiveIndexing(Points* point, int n, int *y_sort, int *x_sort, int *superiority_index){
    int i, j, a = 0, b = 0, count = 0;
    
    // Base case
    if (n <= 1){
        return;
    }

    // Division of points in two partitions
    int *div = (int *)malloc(n * sizeof(int));
    for (i = 0; i < (n + 1) / 2; i++){
        j = y_sort[i]; 
        div[i] = point[j].partition; 
        point[j].partition = 0;
    }
    
    for (i = 0; i < n / 2; i++) {
        j = y_sort[(n + 1) / 2 + i]; 
        div[(n + 1) / 2 + i] = point[j].partition; 
        point[j].partition = 1;
    }
    
    int* x0 = (int *)malloc(((n + 1) / 2) * sizeof(int));
    int* x1 = (int *)malloc((n / 2) * sizeof(int));
    
    // Assigning the coordinates of the partitions
    for (i = 0; i < n; ++i) {
        j = x_sort[i];
        if (point[j].partition == 0){
            x0[a++] = j;
        } else if (point[j].partition == 1){
            x1[b++] = j;
        }
    }

    // Recursive calls for calculating superiority index of respective halves
    recursiveIndexing(point, (n+1)/2, y_sort, x0, superiority_index);
    recursiveIndexing(point, n/2, y_sort+(n+1)/2, x1, superiority_index);
    
    // Merging two partitions
    count = 0;
    for (i=0; i<n; ++i) {
        j = x_sort[i];
        if (point[j].partition == 0){
            count++;  
        } else if (point[j].partition == 1){
            superiority_index[j] += count;
        }
    }
    
    for (i = 0; i < n; ++i){ 
        j = y_sort[i]; 
        point[j].partition = div[i]; 
    }

   free(x0); 
   free(x1); 
   free(div);
}

// Divide and Conquer function to display the superiority index
void divide_and_conquer_algorithm(Points *point, int n){
    int* superiority_index = (int*)malloc(n * sizeof(int));
    int* y_sort = (int*)malloc(n * sizeof(int));
    int* x_sort = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i){
        y_sort[i] = i;
        x_sort[i] = i;
    }

    // Sorting according to the coordinates, i.e, 0 for x-coordinate and 1 for y-coordinate
    merge_sort(point, n, y_sort, 1);
    merge_sort(point, n, x_sort, 0);

    // Initializing the result array with 0;
    for (int i = 0; i < n; ++i){
        superiority_index[i] = 0;
    } 
    
    // Recursive Calls
    recursiveIndexing(point, n, y_sort, x_sort, superiority_index);
    
    // Displaying the resultant array
    displayArray(superiority_index, n);

    // Deallocating the allocated space
    free(superiority_index);
    free(x_sort);
    free(y_sort);
}

int main(){
    int n;
    // Inputting the total number of points
    printf("Enter the number of points: ");
    scanf("%d", &n);

    Points* point = (Points *)malloc(n * sizeof(Points));

    // Inputting the coordinates of n points
    printf("-- Enter the points -- \n\n");
    
    for(int i = 0; i < n; i++){
        printf("Enter x-coordinate of Point %d: ", i+1);
        scanf("%Lf", &point[i].coordinates[0]);
        printf("Enter y-coordinate of Point %d: ", i+1);
        scanf("%Lf", &point[i].coordinates[1]);
        point[i].partition = -1;
        printf("\n");
    }

    // Displaying the original points 
    printf("+++ The original points:\n");

    for(int i = 0; i < n; i++){
        printf("(%Lf,%Lf) ", point[i].coordinates[0], point[i].coordinates[1]);
        if(i % 2){
            printf("\n");
        }
    }

    // Using the quadratic time algorithm to display the superiority indices
    printf("\n\n+++ Superiority indices (quadratic-time):\n");
    quadratic_time_algorithm(point, n);

    // Using the divide and conquer algorithm to display the superiority indices
    printf("\n+++ Superiority indices (divide-and-conquer):\n");
    divide_and_conquer_algorithm(point, n);

    return 0;
}
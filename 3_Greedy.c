// Name: Ritabrata Das
// Roll No. : 20CS8002

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

// Function that returns the number of factors of 2 of the number
int checkFactor(int n){
    int count = 0;

    while(n % 2 == 0){
        count++;
        n /= 2;
    }

    return count;
}

// Function where the only operations permitted are decrement by 1 and division by 2 only if n is even
void greedy1(int n){
    int count = 0;
    printf("    Start     : %d\n", n);
    // Loop to calculate the number of steps until the number remains greater than 1
    while(n > 1){
        count++;

        if(n % 2){
            n--;
            printf("    Decrement : %d\n", n);
        } else {
            n /= 2;
            printf("    Divide    : %d\n", n);
        }
    }

    printf("--- Number of steps = %d\n", count);
}

// Function where the only operations permitted are decrement by 1 or increment by 1 and division by 2 only if n is even
void greedy2(int n){
    int count = 0;
    printf("    Start     : %d\n", n);
    // Loop to calculate the number of steps until the number remains greater than 1
    while(n > 1){
        count++;

        if(n % 2){
            // Condition to check the number for which the number of factors of two are greater
            if (checkFactor(n-1) >= checkFactor(n+1)){
                n--;
                printf("    Decrement : %d\n", n);
            } else {
                n++;
                printf("    Increment : %d\n", n);
            }
        } else {
            n /= 2;
            printf("    Divide    : %d\n", n);
        }
    }

    printf("--- Number of steps = %d\n", count);
}

// Function where the only operations permitted are increment by one of the k-sized array and division by 2 only if n is even
void greedy3(int n, int *a, int k){
    int count = 0;
    printf("    Start     : %d\n", n);
    // Loop to calculate the number of steps until the number remains greater than 1
    while(n > 1){
        count++;

        if(n % 2){
            int maximum = 0;
            // Condition to check the number for which the number of factors of two are greater n + a[i] or n + maximum, where i belongs to the range [a0...ak-1]
            for(int i = 0; i < k; i++){
                if((n + a[i] > 1) && (checkFactor(n + a[i]) > checkFactor(n + maximum))){
                    maximum = a[i];
                }
            }
            printf("    Add %d    : %d\n", maximum, n);
            n += maximum;
        } else {
            n /= 2;
            printf("    Divide    : %d\n", n);
        }
    }

    printf("--- Number of steps = %d\n", count);
}

void optimal(int n, int *a, int k){
    int num = n, counter = 0, count = 0, check = 0, flag = 1, j;

    // Loop to right shift the number and find the highest power possible 
    while (num > 1){
        counter++;
        num = num >> 1;
    }

    num = n + 10 * counter;

    // Initialisation of two arrays of size num + 1
    int * val = (int *)malloc((num + 1) * sizeof(int));
    int * a2 = (int *)malloc((num + 1) * sizeof(int));

    // Loop to initialise the two arrays
    for (int i = 0; i <= num; ++i){
        a2[i] = -1;
        if(i == 1){
            val[i] = 0;
        } else {
            val[i] = 1e7;
        }
    }

    // Loop to get the updated value of a2 from a, where the possibilities of the exact power of two can be achieved
    while(true){
        flag = 0;
        check++;
        for (int i = 2; i <= num; i++){
            if (i % 2 == 0){
                j = i / 2;
                if (val[j] + 1 < val[i]){
                    val[i] = val[j] + 1;
                    a2[i] = k;
                    flag++;
                }
            }
            // Loop to update a2 from a 
            for (int m = 0; m < k; m++){
                j = i + a[m];
                if ((j > 0) && (j <= num) && (val[j] + 1 < val[i])){
                    val[i] = val[j] + 1;
                    a2[i] = m;
                    flag++;
                }
            }
        }

        if(flag == 0){
            break;
        }
    }

    printf("    Start     : %d\n", n);

    // Loop to calculate the number of steps until the number remains greater than 1
    while (n > 1){
        count++;

        // Condition to check for the new values of a2, such that the exact power of 2 can be obtained using right shift
        if (a2[n] == k){
            n = n >> 1;
            printf("    Divide    : %d\n", n);
        } else if (a2[n] > -1) {
            check = a2[n];
            n += a[check];
            printf("    Add %d    : %d\n", a[check], n);
        }
    }

    // Deallocating the space
    free(val);
    free(a2);
    printf("--- Number of steps = %d\n", count);
}


int main(){
    int n, k;

    printf("n = ");
    scanf("%d", &n);

    printf("\n+++ Greedy 1\n");
    greedy1(n);

    printf("\n+++ Greedy 2\n");
    greedy2(n);

    printf("\nk = ");
    scanf("%d", &k);

    int a[k];
    for(int i = 0; i < k; i++){
        scanf("%d", &a[i]);
    }

    printf("\n+++ Greedy 3\n");
    greedy3(n, a, k);

    printf("\n+++ Greedy 4\n");
    optimal(n, a, k);
    printf("\n");

    return 0;
}

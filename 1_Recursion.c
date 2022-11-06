#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to get the total number of ways to climb the stairs by recursion.
long long int getPossibilitiesByRecursion(int n){
    if (n == 0){
        return 1;
    } else if (n < 0){
        return 0;
    } 
    return getPossibilitiesByRecursion(n - 3) + getPossibilitiesByRecursion(n - 2) + getPossibilitiesByRecursion(n - 1);
}

// Function to get the total number of ways to climb the stairs by iteration.
long long int getPossibilitiesByIteration(int n){
    long long int arr[n + 1], i = 3;
    arr[0] = arr[1] = 1;
    arr[2] = 2;
    for (; i <= n; i++){
        arr[i] = arr[i - 1] + arr[i - 2] + arr[i - 3];
    } 
    return arr[n];
}

// Function to get the exact number of ways to climb the stairs by recursion in the range [0, n].
long long int getExactPossibilitiesByRecursion(int n, int m){
    if (n <= 0 || m <= 0 || m*3 < n) {
        return 0;
    } else if (n <= 3 && m == 1) {
        return 1;
    }
    return getExactPossibilitiesByRecursion(n-1, m-1) + getExactPossibilitiesByRecursion(n-2, m-1) + getExactPossibilitiesByRecursion(n-3, m-1);
}

// Function to get the exact number of ways to climb the stairs by iteration(dynamic programming) in the range [0, n].
long long int getExactPossibilitiesByIteration(int n, int m){
    int i, j;
    long long int arr1[38] = {0}, arr2[38] = {0}, arr3[38] = {0};
	arr1[0] = arr2[1] = arr3[1] = arr3[2] = 1;

	for (i = 3; i <= n; i++){
		long long int dp[38] = {0};
		for (j = 1; j <= m; j++){
			int step1=arr1[j - 1];
			int step2=arr2[j - 1];
			int step3=arr3[j - 1];
			
            int total = step1 + step2 + step3;
			dp[j] = total;
		}

		for (j = 0; j <= m; j++){
			arr1[j] = arr2[j];
        }

		for (j = 0; j <= m; j++){
			arr2[j] = arr3[j];
        }

		for (j = 0; j <= m; j++){
			arr3[j] = dp[j];
        }
	}
	return arr3[m];
}

int main(){
    int n;
    // Inputting the total number of stairs
    printf("n = ");
    scanf("%d", &n);

    printf("+++ Any number of jumps...\n\n");
    long long int possibilities;

    // Print the total number of possibilities by recursion.
    possibilities = getPossibilitiesByRecursion(n);
    printf("\tRecursive function returns count = %lld\n\n", possibilities);

    // Print the total number of possibilities by iteration.
    possibilities = getPossibilitiesByIteration(n);
    printf("\tIterative function returns count = %lld\n\n", possibilities);

    // Recurrence Relation: T(n) = T(n-1) + T(n-2) + T(n-3), where T(3) = 1, T(2) = 1, T(1) = 1, T(0) = 0
    printf("+++ Fixed number of jumps...\n\n");
    long long int sum;

    // Print the exact number of possibilities by recursion in the range [0, n].
    sum = 0;
    for(int m = 0; m <= n; m++){
        possibilities = getExactPossibilitiesByRecursion(n, m);
        printf("\tRecursive function returns count = %12lld for m = %2d\n", possibilities, m);
        sum += possibilities;
    }
    printf("\t----------------------------------------------------\n");
    printf("\tTotal number of possibilities = \t%lld\n\n", sum);

    // Print the exact number of possibilities by iteration in the range [0, n].
    sum = 0;
    for(int m = 0; m <= n; m++){
        possibilities = getExactPossibilitiesByIteration(n, m);
        printf("\tIterative function returns count = %12lld for m = %2d\n", possibilities, m);
        sum += possibilities;
    }
    printf("\t----------------------------------------------------\n");
    printf("\tTotal number of possibilities = \t%lld\n\n", sum);

    return 0;
}
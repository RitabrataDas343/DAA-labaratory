// Name: Ritabrata Das
// Roll No. : 20CS8002

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

// Realizable function to calculate whether the target value is realizable or not.
void realizable(int *a,int n,int target,int S){
    int **dp=(int **)malloc(sizeof(int *)*(n+1));
    for(int i=0;i<=n;i++){
        dp[i]=(int *)malloc(sizeof(int)*(2*S+1));
        for(int j=0;j<2*S+1;j++){
            dp[i][j]=0;
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=-S;j<=S;j++){
            if(i==0){
                // Assigning 1 and 0 as true and false;
                if(j==0){
                    dp[i][j+S]=1;
                } else {
                    dp[i][j+S]=0;
                }
            } else {
                if(j-a[i-1]+S>=0){
                    if(dp[i-1][j+S-a[i-1]]>=1){
                        dp[i][j+S]=1;
                    }
                }
                if(j+a[i-1]+S<=2*S){
                    if(dp[i-1][j+S+a[i-1]]>=1){
                        if(dp[i][j+S]==0){
                            dp[i][j+S]=2;
                        } else {
                            dp[i][j+S]=3;
                        }
                    }
                }
            }
        }
    }
    if(dp[n][S+target]>=1){
        printf("The given target value is realizable\n");
    } else {
        printf("The given target value is not realizable\n");
    }
}

// Recursively counting the path from one column to another
void countPath(int *a,int n,int N,int col,int **dp,int *count){
    if(n==0){
        (*count)++;
        return;
    }
    if(dp[n][col]==1){
        countPath(a,n-1,N,col-a[n-1],dp,count);
    }
    else if(dp[n][col]==2){
        countPath(a,n-1,N,col+a[n-1],dp,count);
    }
    else if(dp[n][col]==3){
        countPath(a,n-1,N,col+a[n-1],dp,count);
        countPath(a,n-1,N,col-a[n-1],dp,count);
    }
}

// Recursively printing the path from one column to another
void printPath(int *a,int n,int N,int col,int **dp,int *path){
    if(n==0){
        int sum=0;
        for(int i=0;i<N;i++){
            sum+=path[i];
            if(path[i]<0){
                printf("%d ",path[i]);
            } else {
                printf("+%d ",path[i]);
            }
        }
        printf("\n",sum);
        return;
    }

    if(dp[n][col]==1){
        path[n-1]=a[n-1];
        printPath(a,n-1,N,col-a[n-1],dp,path);
    } else if(dp[n][col]==2){
        path[n-1]=-a[n-1];
        printPath(a,n-1,N,col+a[n-1],dp,path);
    } else if(dp[n][col]==3) {
        path[n-1]=-a[n-1];
        printPath(a,n-1,N,col+a[n-1],dp,path);
        path[n-1]=a[n-1];
        printPath(a,n-1,N,col-a[n-1],dp,path);
    }
}

// Show any one of the realizable paths 
void showone(int *a,int n,int target,int S){
    int **dp=(int **)malloc(sizeof(int *)*(n+1));
    
    for(int i=0;i<=n;i++){
        dp[i]=(int *)malloc(sizeof(int)*(2*S+1));
        for(int j=0;j<2*S+1;j++){
            dp[i][j]=0;
        }
    }
    
    for(int i=0;i<=n;i++){
        for(int j=-S;j<=S;j++){
            if(i==0){
                if(j==0){
                    dp[i][j+S]=1;
                } else {
                    dp[i][j+S]=0;
                }
            } else {
                if(j-a[i-1]+S>=0){
                    if(dp[i-1][j+S-a[i-1]]>=1){
                        dp[i][j+S]=1;
                    }
                }
                if(j+a[i-1]+S<=2*S){
                    if(dp[i-1][j+S+a[i-1]]>=1){
                        if(dp[i][j+S]==0){
                            dp[i][j+S]=2;
                        } else {
                            dp[i][j+S]=3;
                        }
                    }
                }
            }
        }
    }

    if(dp[n][S+target]>=1){
        int col=target+S;
        printf("One of the realizeable paths:\n");
        int *path=(int *)malloc(sizeof(int)*n);
        for(int i=n;i>=1;i--){
            if(dp[i][col]==1){
                path[i-1]=a[i-1];
                col-=a[i-1];
            } else {
                path[i-1]=-a[i-1];
                col+=a[i-1];
            }
        }
        for(int i=0;i<n;i++){
            if(path[i]>=0){
                printf("+%d ",path[i]);
            } else {
                printf("%d ",path[i]);
            }
        }
        printf("\n");
    }
}

// Show all of the realizable paths 
void showall(int *a,int n,int target,int S){
    int **dp=(int **)malloc(sizeof(int *)*(n+1));
    for(int i=0;i<=n;i++){
        dp[i]=(int *)malloc(sizeof(int)*(2*S+1));
        for(int j=0;j<2*S+1;j++){
            dp[i][j]=0;
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=-S;j<=S;j++){
            if(i==0){
                if(j==0){
                    dp[i][j+S]=1;
                } else {
                    dp[i][j+S]=0;
                }
            } else {
                if(j-a[i-1]+S>=0) {
                    if(dp[i-1][j+S-a[i-1]]>=1) {
                        dp[i][j+S]=1;
                    }
                }
                if(j+a[i-1]+S<=2*S) {
                    if(dp[i-1][j+S+a[i-1]]>=1){
                        if(dp[i][j+S]==0){
                            dp[i][j+S]=2;
                        } else {
                            dp[i][j+S]=3;
                        }
                    }
                }
            }
        }
    }
    
    if(dp[n][S+target]>=1){
        int col=target+S;
        int *path=(int *)malloc(sizeof(int)*n);
        int c=0;
        int *count=&c;
        countPath(a,n,n,target+S,dp,count);
        printf("Number of realizeable paths: %d\n",c);
        printf("All of the realizeable paths:\n");
        printPath(a,n,n,target+S,dp,path);
    }
}

int main(){
    // Inputting the number of elements.
    int n;
    printf("Enter number of elements:");
    scanf("%d",&n);

    int *a = (int *)malloc(sizeof(int)*n);
    // Storing the elements in the array.
    
    printf("Enter the elements:\n");
    int S = 0;
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        S += a[i];
    }

    // Enter the target value to be realised.
    int T;
    printf("Enter target value:");
    scanf("%d",&T);

    // Calling of the realizable function.
    realizable(a,n,T,S);

    // Calling of the showone function.
    showone(a,n,T,S);

    // Calling of the showall function.
    showall(a,n,T,S);

    return 0;
}
// Name: Ritabrata Das
// Roll No.: 20CS8002

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <strings.h>

// Defining the structure of vertex having vertex, weight and edge, with visited boolean and link.
typedef struct vertex{
    int v, w, e, visited;
    list* link;
} vertex;

// Defining the structure of list having vertex struct, weight and edge, with struct list of next.
typedef struct list{
    struct vertex* vp;
    int v, w;
    struct list* next;
} list;

// Globally defining 'n' and 'Vtx' array of vertex.
int n;
vertex *Vtx;

// Function to add the elements to the adjacency list of the graph.
void addToAdjacencyList(vertex *v1, vertex *v2, int weight, int val){
    list *l = (list*)malloc(sizeof(list));
    l->next = v1->link;
    v1->link = l;
    l->vp = v2;
    l->w = weight;
    l->v = val;
}

// Function to get the sum of the elements of the graph.
int totalSum(vertex *v,int edge){
    int sum = v->w;
    list *p = v->link;
    v->visited = 1;
    while(p != NULL){
        if(p->v != edge && p->vp->visited == 0){
            sum += totalSum(p->vp, edge);
        }
        p = p->next;
    }
    v->visited = 0;
    return sum;
}

// Depth first Search function to get the minimum vulnerability of the graph.
int dfs(vertex *v, int sum, int *me1, int *me2, int *max){
    int totsum, vul, dfssum=0;
    v->visited = 1;
    list *p = v->link;
    while(p != NULL){
        if(p->vp->visited == 0){
            totsum = dfs(p->vp, sum+v->w, me1, me2, max);
            dfssum += totsum;
            vul = p->w - abs(totsum - sum);
            if(*max < vul){
                *max = vul;
                *me1 = v->v;
                *me2 = p->vp->v;
            }
        }
        p = p->next;
    }
    v->visited = 0;
    return dfssum + v->w;
}

// Bruteforce algorithm of O(n^2) time complexity to find the minimum vulnerability.
void BruteForce(vertex *V,int n){
    int max = INT_MIN, min1 = 0, min2 = 0, vul, s1, s2;
    list *p;
    for(int i = 0; i < n; i++){
        p = V[i].link;
        while(p != NULL){
            if(V[i].e && p->vp->e > 0){
                p->vp->e--;
                V[i].e--;
                vul = p->w - abs(totalSum(&V[i], p->v) - totalSum(p->vp, p->v));
                if(max < vul){
                    max = vul;
                    min1 = i + 1;
                    min2 = p->vp->v;
                }
            }
            p = p->next;
        }
    }
    printf("Edge with the smallest vulnerability computed using first method: %d %d\n", min1, min2);
}

// Linear Time algorithm of O(n) time complexity to find the minimum vulnerability.
void LinearTime(vertex *V,int n){
    int min1, min2, max = INT_MIN;
    dfs(V, V->w, &min1, &min2, &max);
    printf("Edge with the smallest vulnerability computed using second method: %d %d\n", min1, min2);
}

int main(){
    int edge1, edge2, weight;

    // Inputting the number of vertex
    printf("Write n: ");
    scanf(" %d",&n);

    // Initializing the array of type vertex
    Vtx = (vertex*)malloc(n * sizeof(vertex));

    // Determine the weights of the vertices of struct vertex
    printf("Write weights of vertices: ");
    for(int i = 0; i < n; i++){
        scanf(" %d", &Vtx[i].w);
        Vtx[i].v = i+1;
        Vtx[i].visited = 0;
        Vtx[i].link = NULL;
        Vtx[i].e = 0;
    }

    // Determine the weights of the edges and appending it to the end of the adjacency list
    printf("Write the edges and their weights\n");
    for(int i = 0; i < n-1; i++){
        scanf(" %d %d %d",&edge1, &edge2, &weight);
        edge1--;
        edge2--;
        Vtx[edge1].e++;
        Vtx[edge2].e++;
        addToAdjacencyList(&Vtx[edge1], &Vtx[edge2], weight, i+1);
        addToAdjacencyList(&Vtx[edge2], &Vtx[edge1], weight, i+1);
    }

    // Call to Bruteforce algorithm function
    BruteForce(Vtx,n);

    // Call to Linear Time algorithm function
    LinearTime(Vtx,n);

    return 0;
}
	

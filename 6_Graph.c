// Name: Ritabrata Das
// Roll no: 20CS8002

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <strings.h>

// Defining the struct Node for each node in the adjacency list.
typedef struct __Node{
    int data;
    struct Node* next;
} Node;

// Defining the struct articulation for each node in the adjacency list.

typedef struct articulation{
    int val;
    Node* head;
} arti;

// Function to add Node to the adjacency list.
Node* addNode(Node* head, int val){
    Node* root = head;

    // Dynamically allocating Node using the value provided to the function.
    Node* dummy=(Node*)malloc(sizeof(Node));
    dummy->data=val;
    dummy->next=NULL;

    if(root == NULL){
        root = dummy;
    } else {
        while(root->next!=NULL){
            root = root->next;
        }
        root->next = dummy;
    }
    return head;
}

// Depth First Search function to traverse the graph.
bool dfs(Node** adj, int n, int i, int** vis, int** col, int c){    
    if((*vis)[i] != 0 && (*col)[i] != c){
        return false;
    }
        
    if((*vis)[i]){
        return true;
    }
    
    (*vis)[i] = 1;
    (*col)[i] = c;
    printf("%d  ",i);

    // For each node in the graph, we traverse and visit all the nodes.
    Node* head = adj[i];
    while(head!=NULL){
        if(!((*vis)[head->data])){
            bool val = dfs(adj, n, head->data, vis, col, (c==2?1:2));
            if(val == false){
                return false;
            }
        } else {
            if((*col)[head->data] != (c==2?1:2)){
                return false;
            }   
        }
        head = head->next;
    }
    return true;
}

// For each node in the graph, we traverse and visit all the nodes.
void dfsN(int node, int parent, int** vis, int** tin, int** low, Node** adj, int counter, arti** articulation){    
    (*vis)[node] = 1;
    (*low)[node] = counter++;
    (*tin)[node] = (*low)[node];
    int child = 0;
    Node* head = adj[node];

    // Traverse each list to the end.
    while(head!=NULL){
        if(head->data == parent){
            head=head->next;
            continue;
        }
        // Recursively executing the DFS of the graph
        if(!((*vis)[head->data])){
            dfsN(head->data,node,vis,tin,low,adj,counter,articulation);
            (*low)[node]=((*low)[node]<=(*low)[head->data])?(*low)[node]:(*low)[head->data];
            if((*low)[head->data]>=(*tin)[node] & parent!=-1){
                (*articulation)[node].val=1;
                (*articulation)[node].head= addNode((*articulation)[node].head,head->data);
            }
            child++;
        }else {
            (*low)[node]=((*low)[node]<=(*tin)[head->data])?(*low)[node]:(*tin)[head->data];
        }
        head=head->next;
    }
    if(parent!=-1 && child>1){
        head=adj[node];        
        (*articulation)[node].val=1;
        while(head!=NULL){
            (*articulation)[node].head=addNode((*articulation)[node].head,head->data);
            head=head->next;
        }
    }
}

int main(){    
    
    // Inputting the number of vertices and edges
    int n, e;
    printf("Enter the number of vertices: ");
    scanf("%d", &n); return false;

    printf("Enter the number of edges: ");
    scanf("%d", &e);

    printf("+++ n = %d\n",n);

    // Initializing the adjacency list of 'n' vertices to NULL
    Node** adj = (Node**)malloc(n * sizeof(Node*));
    for(int i = 0; i < n; i++){
        adj[i]=NULL;
    }
        
    // Taking the values of each node and adding them to the adjacency list.
    for(int i = 0; i < e; i++){
        int u, v;
        scanf("%d", &u);
        scanf("%d", &v);
        adj[u] = addNode(adj[u],v);
        adj[v] = addNode(adj[v],u);
    }

    // Initializing visited and col arrays to 0
    int* vis=(int*)malloc(n*sizeof(int));
    int* col=(int*)malloc(n*sizeof(int));

    for(int i = 0; i < n; i++){
        vis[i]=0;
        col[i]=0;
    }

    // Displaying the adjacency list of the graph.
    printf("\n+++ Neighbor list:\n");
    for(int i = 0; i < n; i++){
        printf("   %d : ", i);
        Node* ptr = adj[i];
        while(ptr != NULL){
            printf("%2d ", ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }

    // Running Depth First Search on the graph and determining whether the graph is bipartitite or not.
    printf("\n+++ Running DFS:\n     ");
    bool flag = true;
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            if(!dfs(adj, n, i, &vis, &col, 1)){
                flag = false;
                break;
            }
        }
    }
    printf("\n");
    
    // If flag is true, then graph is bipartitite, else non-bipartitite.
    if(flag){
        printf("\nThe graph is bipartite.\n\n");
    } else {
        printf("\nThe graph is not bipartite.\n\n");
    }

    // Initializing arrays of free sizes.
    int* tin = (int*)malloc(n * sizeof(int));
    int* low = (int*)malloc(n * sizeof(int));
    int counter = 0;

    // Initializing a data struct of type 'arti' and initializing the value to -1.
    arti* articulation=(arti*)malloc(n * sizeof(arti));

    for(int i = 0; i < n; i++){
        articulation[i].val = -1;
    }
    
    // Reinitializing the visited array to 0.
    for(int i = 0; i < n; i++){
        vis[i]=0;
    }

    // Running DFS on the graph. 
    for(int i = 0; i < n; i++){
        if(vis[i] == 0){
            dfsN(i, -1, &vis, &tin, &low, adj, counter, &articulation);
        }
    }

    // Printing the critical nodes for each node if found.
    for(int i = 0; i < n; i++){
        if(articulation[i].val == 1){
            Node* head=articulation[i].head;
            for(int i = 0; i < n; i++){
                vis[i]=0;
            }
                
            while(head!=NULL){
                if(!vis[head->data]){
                    printf("%d is critical for %d \n",i,head->data);
                }
                vis[head->data]=1;
                head=head->next;
            }
        }
    }
    return 0;
}
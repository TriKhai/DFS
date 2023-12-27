#include "stdio.h"
#define MAX_Vertices 20
#define MAX_Lenght 20
#define MAX_Elements 20

typedef struct {
	int A[MAX_Vertices][MAX_Vertices];
	int n;
}Graph;


//LIST
typedef struct {
	int data[MAX_Lenght];
	int size;
} List;

void make_null_List(List *list) {
	list->size = 0;
}

void push_List(List *list, int x) {
	list->data[list->size] = x;
	list->size++;
}

int retrieve(List *list, int i) {
	return list->data[i-1];
}

////STACK
//typedef struct {
//	int data[MAX_Elements];
//	int size;
//} Stack;
//
//void make_null_Stack(Stack *stack) {
//	stack->size = 0;
//}
//
//int empty_Stack(Stack *stack) {
//	return stack->size == 0;
//}
//
//void push_Stack(Stack *S, int x) {
//	S->data[S->size] = x;
//	S->size++;
//}
//
//void pop_Stack(Stack *S) {
//	S->size--;
//}
//
//int top_Stack(Stack *S) {
//	return S->data[S->size-1];
//}

//GRAPH

void init(Graph *G, int n) {
	int i, j;
	G->n = n;
	for(i=1; i<=G->n; i++) {
		for(j=1; j<=G->n; j++) {
			G->A[i][j] = 0;
		}
	}
}

void add_Edge(Graph *G, int x, int y) {
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

int adjacent(Graph *G, int x, int y) {
	return G->A[x][y] != 0;
}

int degree(Graph *G, int n) {
	int i;
	int deg = 0;
	for(i=1; i<=G->n; i++) {
		if(adjacent(G, i, n)) {
			deg++;
		}
	}
	return deg;
}

List neightbors(Graph *G, int n) {
	int i;
	List list;
	make_null_List(&list);
	for(i=1; i<=G->n; i++) {
		if(adjacent(G, i, n)) {
			push_List(&list, i);
		}
	}
	return list;
}

int Mark[MAX_Vertices];
int parent[MAX_Vertices];
void DFS_Recursion(Graph *G, int u, int p) {
	int v, i;
	if(Mark[u] == 1)
		return;
//	printf("%d\n", n);
	parent[u] = p;
	Mark[u] = 1;
	List list = neightbors(G, u);
	for(i=1; i<=list.size; i++) {
		v = retrieve(&list, i);
		DFS_Recursion(G, v, u);
	}
}


int main() {
	Graph G;
	freopen("graph.txt", "r", stdin);
	int i, j, n, m, u, v;
	scanf("%d%d", &n, &m);
	init(&G, n);
	for(i=1; i<=m; i++){
		scanf("%d%d", &u, &v);
		add_Edge(&G, u, v);
	}
	for(i=1; i<=n; i++) {
		Mark[i] = 0;
		parent[i] = -1;
	}

//	DFS_Recursion(&G, 1, 0);

	for(i=1; i<=n; i++) {
		if(Mark[i] == 0) 
			DFS_Recursion(&G, i, 0);
	}

	for(i=1; i<=n; i++) {
		printf("%d %d\n", i, parent[i]);
	}	
	return 0;
}

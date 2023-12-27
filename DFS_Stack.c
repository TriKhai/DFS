#include "stdio.h"
#define MAX_Vertices 20
#define MAX_Lenght 20
#define MAX_Stack 40

typedef struct {
	int A[MAX_Vertices][MAX_Vertices];
	int n;
} Graph;

typedef struct {
	int data[MAX_Lenght];
	int size;
} List;

typedef struct {
	int data[MAX_Stack];
	int size;	
} Stack;

//LIST
void makenullList(List *list) {
	list->size = 0;
}

void insertList(List *list, int x) {
	list->data[list->size] = x;
	list->size++;
} 

int retrieve(List *list, int i) {
	return list->data[i-1];
}

//STACK
void make_null_Stack(Stack *S) {
	S->size = 0;
}

void push(Stack *S, int x) {
	S->data[S->size] = x;
	S->size++;
}

void pop(Stack *S) {
	S->size--;
}

int top(Stack *S) {
	return S->data[S->size-1];
}

int empty(Stack *S) {
	return S->size == 0;
}

//GRAPH
void init_Graph(Graph *G, int n) {
	int i, j;
	G->n = n;
	for(i = 1; i<=G->n; i++) 
		for(j=1; j<=G->n; j++) 
			G->A[i][j] = 0;
}

void add_Edge(Graph *G, int x, int y) {
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

int adjacent(Graph *G, int x, int y) {
	return G->A[x][y] != 0;
}

void print_Graph(Graph *G) {
	int i, j;
	for(i=1; i<=G->n; i++) {
		for(j=1; j<=G->n; j++) {
			printf("%d ", G->A[i][j]);
		}
		printf("\n");
	}
}

int degree(Graph *G, int n) {
	int deg = 0;
	int i;
	for(i=1; i<=G->n; i++) {
		if(adjacent(G, i, n))
			deg++;
	}
	return deg;
}

List neighbors(Graph *G, int x) {
	List L;
	makenullList(&L);
	int i;
	for(i=1; i<=G->n; i++) {
		if(adjacent(G, i, x))
			insertList(&L, i);
	}
	return L;
}

List DFS_khong_lien_thong(Graph *G, int n) {
	int i, j, mark[MAX_Vertices], u, v;
	Stack S;
	List L, Save;
	makenullList(&Save);
	make_null_Stack(&S);
	push(&S, n);
	for(i = 1; i<=G->n; i++) {
		mark[i] = 0;
	}
	while(!empty(&S)) {
		u = top(&S);
		pop(&S);
		if(mark[u] == 1) 
			continue;
		insertList(&Save, u);
		mark[u] = 1;
		L = neighbors(G, u);
		for(i=1; i<=L.size; i++) {
			v = retrieve(&L, i);
			if(mark[v] == 0) 
				push(&S, v);
		}
	}
	return Save;
}

void DFS_lien_thong(Graph *G, int n) {
	int i, j, mark[MAX_Vertices], u, v;
	Stack S;
	List L;
	make_null_Stack(&S);
	push(&S, n);
	for(i = 1; i<=G->n; i++) {
		mark[i] = 0;
	}
	while(!empty(&S)) {
		u = top(&S);
		pop(&S);
		if(mark[u] == 1) 
			continue;
		printf("%d ", u);
		mark[u] = 1;
		L = neighbors(G, u);
		for(i=1; i<=L.size; i++) {
			v = retrieve(&L, i);
			if(mark[v] == 0) 
				push(&S, v);
		}
	}
}

List DFS_parent(Graph *G, int n, int parent[]) {
	int i, j, mark[MAX_Vertices], u, v;
	Stack S;
	List L, Save;
	makenullList(&Save);
	make_null_Stack(&S);
	push(&S, n);
	parent[n] = 0;
	for(i = 1; i<=G->n; i++) {
		mark[i] = 0;
	}
	while(!empty(&S)) {
		u = top(&S);
		pop(&S);
		
		if(mark[u] == 1) 
			continue;
		insertList(&Save, u);
		mark[u] = 1;
		L = neighbors(G, u);
		for(i=1; i<=L.size; i++) {
			v = retrieve(&L, i);
			if(mark[v] == 0) {
				push(&S, v);
				parent[v] = u;
			} 
		}
	}
	return Save;
}

int main( ) {
	Graph G;
	int n, m, u, v, i ,j;
	freopen("graph.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	for(i=1; i<=m; i++) {
		scanf("%d%d", &u, &v);
		add_Edge(&G, u, v);
	}
	print_Graph(&G);

	int a = 1, b = 2;
	printf("\nKT %d va %d co lan can khong?", a, b);
	printf("\t%d", adjacent(&G, a, b));
	printf("\nBac cua dinh: ");
	printf("%d", degree(&G, 1));
	printf("\nLang gieng: ");
	List L = neighbors(&G, 1);
	for(i=1; i<=L.size; i++) {
		printf("%d ", retrieve(&L, i));
	}
	
	printf("\n\n\nDFS lien thong\n");
	DFS_lien_thong(&G, 1);	
	
	printf("\n\n\nDFS khong lien thong\n");
	int mark[MAX_Vertices];
	for(i=1; i<=G.n; i++) {
		mark[i] = 0;
	}
	for(i=1; i<=G.n; i++) {
		if(mark[i] == 0) {
			List list_dfs = DFS_khong_lien_thong(&G, i);
			for(j=1; j<=list_dfs.size; j++) {
				int k = retrieve(&list_dfs, j);
					printf("%d ", k);
					mark[k] = 1;
			}
		}
	}
	
//	parent
	printf("\n\n");
	int parent[MAX_Vertices];
	for(i=1; i<=G.n; i++) {
		parent[i] = -1;
	}
	List list_dfs_parent = DFS_parent(&G, 1, parent);
	for(i=1; i<=G.n; i++) {
		printf("Dinh = %d, Parent = %d\n", i, parent[i]);
	}
	return 0;
}


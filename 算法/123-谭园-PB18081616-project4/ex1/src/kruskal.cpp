#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
typedef struct edge {
	int v1;
	int v2;
	int w;
}edge;
typedef struct {
	int arcnum, vexnum;
}algraph;
typedef struct sset {			//不相交集合
	int data;
	int rank;
	struct sset* p;
}sset, * pset;
typedef struct linklist {				//kruskal 
	int data;
	struct linklist* next;
}linklist, * plinklist;
void max_heapify(edge a[], int i, int heapsize); //堆排序 
void build_max_heap(edge a[], int heapsize, int N);
void heap_sort(edge a[], int N);
void make_set(pset x);
pset find_set(pset x);
void link(pset x, pset y);
void union_set(pset x, pset y);
void edgegen(algraph G, FILE* fp, edge* edges);	//记录边
plinklist kruskal(algraph G, edge* edges);
void output(plinklist mst, edge* arcset, FILE* fp);
 


 
int main() {
	algraph G;
	edge* edges;
	plinklist zuixiao;
	int i, j, v1, v2, w;
	double run_time;						 
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	double dqFreq;
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	FILE* i1, * i2, * i3, * i4, * o1, * o2, * o3, * o4;
	i1 = fopen("input1.txt", "r");
	i2 = fopen("input2.txt", "r");
	i3 = fopen("input3.txt", "r");
	i4 = fopen("input4.txt", "r");
	o1 = fopen("result1.txt", "w");
	o2 = fopen("result2.txt", "w");
	o3 = fopen("result3.txt", "w");
	o4 = fopen("result4.txt", "w");
	G.vexnum = 8;								 
	G.arcnum = 0;
	while (!feof(i1)) {						
		if (getc(i1) == '\n')
			G.arcnum++;
	}
	fseek(i1, 0L, 0);
	edges = (edge*)malloc(G.arcnum * sizeof(edge));
	edgegen(G, i1, edges);				
	QueryPerformanceCounter(&time_start);
	zuixiao = kruskal(G, edges);
	QueryPerformanceCounter(&time_over);		 
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	output(zuixiao, edges, o1);
	fprintf(o1, "边：%d\n运行时间：%lfms\n", G.arcnum, run_time);
	G.vexnum = 64;								
	G.arcnum = 0;
	while (!feof(i2)) {						
		if (getc(i2) == '\n')
			G.arcnum++;
	}
	fseek(i2, 0L, 0);
	edges = (edge*)malloc(G.arcnum * sizeof(edge));
	edgegen(G, i2, edges);				
	QueryPerformanceCounter(&time_start);
	zuixiao = kruskal(G, edges);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	output(zuixiao, edges, o2);
	fprintf(o2, "边：%d\n运行时间：%lfms\n", G.arcnum, run_time);
	G.vexnum = 128;							
	G.arcnum = 0;
	while (!feof(i3)) {						
		if (getc(i3) == '\n')
			G.arcnum++;
	}
	fseek(i3, 0L, 0);
	edges = (edge*)malloc(G.arcnum * sizeof(edge));
	edgegen(G, i3, edges);				
	QueryPerformanceCounter(&time_start);
	zuixiao = kruskal(G, edges);
	QueryPerformanceCounter(&time_over);	
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	output(zuixiao, edges, o3);
	fprintf(o3, "边：%d\n运行时间：%lfms\n", G.arcnum, run_time);
	G.vexnum = 512;							
	G.arcnum = 0;
	while (!feof(i4)) {					
		if (getc(i4) == '\n')
			G.arcnum++;
	}
	fseek(i4, 0L, 0);
	edges = (edge*)malloc(G.arcnum * sizeof(edge));
	edgegen(G, i4, edges);			
	QueryPerformanceCounter(&time_start);
	zuixiao = kruskal(G, edges);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	output(zuixiao, edges, o4);
	fprintf(o4, "边：%d\n运行时间：%lfms\n", G.arcnum, run_time);
}
void max_heapify(edge a[], int i, int heapsize) {		 
	int l, r, largest;
	edge temp;
	l = 2 * i + 1, r = 2 * i + 2;
	if (l <= heapsize && a[l].w > a[i].w)
		largest = l;
	else
		largest = i;
	if (r <= heapsize && a[r].w > a[largest].w)
		largest = r;
	if (largest != i) {
		temp = a[i];
		a[i] = a[largest];
		a[largest] = temp;
		max_heapify(a, largest, heapsize);
	}
}
void build_max_heap(edge a[], int heapsize, int N) {
	for (int i = (N - 1) / 2; i >= 0; i--)
		max_heapify(a, i, heapsize);
}
void heap_sort(edge a[], int N) {
	edge temp;
	int heapsize = N - 1;
	build_max_heap(a, heapsize, N);
	for (int i = N - 1; i > 0; i--) {
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		heapsize--;
		max_heapify(a, 0, heapsize);
	}
}


void make_set(pset x) {
	x->p = x;
	x->rank = 0;
}
pset find_set(pset x) {
	if (x != x->p)
		x->p = find_set(x->p);
	return x->p;
}
void link(pset x, pset y) {
	if (x->rank > y->rank)
		y->p = x;
	else {
		x->p = y;
		if (x->rank == y->rank)
			y->rank = y->rank + 1;
	}
}
void union_set(pset x, pset y) {
	link(find_set(x), find_set(y));
}

void edgegen(algraph G, FILE* fp, edge* edges) {	
	int i, v1, v2, w;
	int j = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &v1, &v2, &w);
		edges[j].v1 = v1;
		edges[j].v2 = v2;
		edges[j++].w = w;
	}
}


plinklist kruskal(algraph G, edge* edges) { 
	int i;
	pset* x;
	plinklist p, head, rear;
	head = rear = NULL;
	x = (pset*)malloc(G.vexnum * sizeof(pset));
	for (i = 0; i < G.vexnum; i++) {
		x[i] = (pset)malloc(sizeof(sset));
		x[i]->data = i;
		make_set(x[i]);
	}
	heap_sort(edges, G.arcnum);
	for (i = 0; i < G.arcnum; i++) {
		if (find_set(x[edges[i].v1]) != find_set(x[edges[i].v2])) {
			p = (plinklist)malloc(sizeof(linklist));
			p->data = i;
			if (head == NULL) {
				head = p;
				rear = p;
			}
			else {
				rear->next = p;
				rear = rear->next;
			}
			union_set(x[edges[i].v1], x[edges[i].v2]);
		}
	}
	rear->next = NULL;
	return head;
}

void output(plinklist mst, edge* arcset, FILE* fp) {		 
	int weight = 0;
	plinklist p = mst;
	while (p != NULL) {
		weight += arcset[p->data].w;
		fprintf(fp, "%d %d %d\n", arcset[p->data].v1, arcset[p->data].v2, arcset[p->data].w);
		p = p->next;
	}
	fprintf(fp, "总权重：%d\n", weight);
}











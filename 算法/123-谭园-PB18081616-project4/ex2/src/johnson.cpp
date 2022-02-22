#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h> 
typedef struct arcnode {
	int adjvex;
	struct arcnode* nextarc;
	int w;
}arcnode;
typedef struct vnode {
	int data;
	int d;
	int parent;
	arcnode* firstarc;
}vnode, * adjlist;
typedef struct {
	adjlist vertices;
	int arcnum, vexnum;
}algraph;
int heapsize;
algraph algraphgen(FILE* fp, int v, int e);
void min_heapify(algraph G, int a[], int i);
void build_min_heap(algraph G, int a[], int N); 
int heap_extract_min(algraph G, int a[]);
void initialize_single_source(algraph& G, int s);
void relax(algraph& G, int u, int v, int w);
bool bellman_ford(algraph& G, int s);
void dijkstra(algraph& G, int s);//利用relax和优先队列实现dijkstra算法 
void output(algraph G, int u, int v, FILE* fp);
void johnson(algraph G, FILE* fp);

int main() {
	double run_time;						
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	double dqFreq;
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	algraph G;
	FILE* i11, * i12, * i21, * i22, * i31, * i32, * i41, * i42;
	FILE* o11, * o12, * o21, * o22, * o31, * o32, * o41, * o42;
	FILE* t;
	i11 = fopen("input11.txt", "r");
	o11 = fopen("result11.txt", "w");
	i12 = fopen("input12.txt", "r");
	o12 = fopen("result12.txt", "w");
	i21 = fopen("input21.txt", "r");
	o21 = fopen("result21.txt", "w");
	i22 = fopen("input22.txt", "r");
	o22 = fopen("result22.txt", "w");
	i31 = fopen("input31.txt", "r");
	o31 = fopen("result31.txt", "w");
	i32 = fopen("input32.txt", "r");
	o32 = fopen("result32.txt", "w");
	i41 = fopen("input41.txt", "r");
	o41 = fopen("result41.txt", "w");
	i42 = fopen("input42.txt", "r");
	o42 = fopen("result42.txt", "w");
	t = fopen("time.txt", "w");
	G = algraphgen(i11, 27, int(log(27) / log(5)));
	QueryPerformanceCounter(&time_start);
	johnson(G, o11);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	fprintf(t, "%lfms\n", run_time);
	G = algraphgen(i12, 27, int(log(27) / log(7)));
	QueryPerformanceCounter(&time_start);
	johnson(G, o12);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	fprintf(t, "%lfms\n", run_time);
	G = algraphgen(i21, 81, int(log(81) / log(5)));
	QueryPerformanceCounter(&time_start);
	johnson(G, o21);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	fprintf(t, "%lfms\n", run_time);
	G = algraphgen(i22, 81, int(log(81) / log(7)));
	QueryPerformanceCounter(&time_start);
	johnson(G, o22);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	fprintf(t, "%lfms\n", run_time);
	G = algraphgen(i31, 243, int(log(243) / log(5)));
	QueryPerformanceCounter(&time_start);
	johnson(G, o31);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	fprintf(t, "%lfms\n", run_time);
	G = algraphgen(i32, 243, int(log(243) / log(7)));
	QueryPerformanceCounter(&time_start);
	johnson(G, o32);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	fprintf(t, "%lfms\n", run_time);
	G = algraphgen(i41, 729, int(log(729) / log(5)));
	QueryPerformanceCounter(&time_start);
	johnson(G, o41);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	fprintf(t, "%lfms\n", run_time);
	G = algraphgen(i42, 729, int(log(729) / log(7)));
	QueryPerformanceCounter(&time_start);
	johnson(G, o42);
	QueryPerformanceCounter(&time_over);		
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	fprintf(t, "%lfms\n", run_time);
}

algraph algraphgen(FILE* fp, int v, int e) {
	int i, j, v1, v2, w;
	algraph G;
	arcnode* pa, * ra = NULL;
	G.vexnum = v;
	G.arcnum = 0;
	while (!feof(fp)) {
		if (getc(fp) == '\n')
			G.arcnum++;
	}
	fseek(fp, 0L, 0);
	G.vertices = (vnode*)malloc(v * sizeof(vnode));
	for (i = 0; i < v; i++) {
		G.vertices[i].firstarc = NULL;
		for (j = 0; j < e; j++) {
			fscanf(fp, "%d %d %d", &v1, &v2, &w);
			pa = (arcnode*)malloc(sizeof(arcnode));
			pa->adjvex = v2;
			pa->w = w;
			if (G.vertices[i].firstarc == NULL) {
				G.vertices[i].firstarc = pa;
				ra = pa;
			}
			else {
				ra->nextarc = pa;
				ra = ra->nextarc;
			}
		}
		ra->nextarc = NULL;
	}
	return G;
}


void min_heapify(algraph G, int a[], int i) {
	int l, r, min;
	int temp;
	l = 2 * i + 1, r = 2 * i + 2;
	if (l <= heapsize && G.vertices[a[l]].d < G.vertices[a[i]].d)
		min = l;
	else
		min = i;
	if (r <= heapsize && G.vertices[a[r]].d < G.vertices[a[min]].d)
		min = r;
	if (min != i) {
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
		min_heapify(G, a, min);
	}
}
void build_min_heap(algraph G, int a[], int N) {
	heapsize = N - 1;
	for (int i = (N - 1) / 2; i >= 0; i--)
		min_heapify(G, a, i);
}
int heap_extract_min(algraph G, int a[]) {
	if (heapsize < 0)
		return -1;
	int min = a[0];
	a[0] = a[heapsize];
	heapsize--;
	min_heapify(G, a, 0);
	return min;
}

void initialize_single_source(algraph& G, int s) {
	for (int i = 0; i < G.vexnum; i++) {
		G.vertices[i].d = 10000000;
		G.vertices[i].parent = -1;
	}
	G.vertices[s].d = 0;
}
void relax(algraph& G, int u, int v, int w) {
	if (G.vertices[v].d > G.vertices[u].d + w) {
		G.vertices[v].d = G.vertices[u].d + w;
		G.vertices[v].parent = u;
	}
}

bool bellman_ford(algraph& G, int s) {			 
	int i, j;
	arcnode* pa;
	initialize_single_source(G, s);
	for (i = 1; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) {
			pa = G.vertices[j].firstarc;
			while (pa != NULL) {
				relax(G, j, pa->adjvex, pa->w);
				pa = pa->nextarc;
			}
		}
	}
	for (j = 0; j < G.vexnum; j++) {
		pa = G.vertices[j].firstarc;
		while (pa != NULL) {
			if (G.vertices[pa->adjvex].d > G.vertices[j].d + pa->w)
				return false;
			pa = pa->nextarc;
		}
	}
	return true;
}

void dijkstra(algraph& G, int s) {			
	initialize_single_source(G, s);
	int v;
	arcnode* pa;
	int* Q;
	Q = (int*)malloc(G.vexnum * sizeof(int));
	for (int i = 0; i < G.vexnum; i++)
		Q[i] = i;
	build_min_heap(G, Q, G.vexnum);
	while (heapsize >= 0) {
		v = heap_extract_min(G, Q);
		pa = G.vertices[v].firstarc;
		while (pa != NULL) {
			relax(G, v, pa->adjvex, pa->w);
			pa = pa->nextarc;
		}
	}
}

void output(algraph G, int u, int v, FILE* fp) {	
	if (u == v || v == -1)
		return;
	output(G, u, G.vertices[v].parent, fp);
	fprintf(fp, ",%d", v);
}

void johnson(algraph G, FILE* fp) {		 
	int i, j;
	int* h;
	int dd;
	algraph Gci;
	arcnode* pa, * ra = NULL;
	Gci.vexnum = G.vexnum + 1;
	Gci.arcnum = G.arcnum + G.vexnum;
	Gci.vertices = (vnode*)malloc(Gci.vexnum * sizeof(vnode));
	for (i = 1; i <= G.vexnum; i++)
		Gci.vertices[i] = G.vertices[i - 1];
	Gci.vertices[0].firstarc = NULL;
	for (i = 1; i <= G.vexnum; i++) {
		pa = (arcnode*)malloc(sizeof(arcnode));
		pa->adjvex = i;
		pa->w = 0;
		if (Gci.vertices[0].firstarc == NULL) {
			Gci.vertices[0].firstarc = pa;
			ra = pa;
		}
		else {
			ra->nextarc = pa;
			ra = ra->nextarc;
		}
	}
	ra->nextarc = NULL;
	h = (int*)malloc(G.vexnum * sizeof(int));
	if (bellman_ford(Gci, 0) == false)
		printf("有负环\n");
	else {
		for (i = 1; i < Gci.vexnum; i++)
			h[i - 1] = Gci.vertices[i].d;
		for (i = 0; i < G.vexnum; i++) {
			pa = G.vertices[i].firstarc;
			while (pa != NULL) {
				pa->w = pa->w + h[i] - h[pa->adjvex];
				pa = pa->nextarc;
			}
		}
		for (i = 0; i < G.vexnum; i++) {
			dijkstra(G, i);
			for (j = 0; j < G.vexnum; j++) {
				if (j != i) {
					fprintf(fp, "(%d", i);
					output(G, i, j, fp);
					dd = G.vertices[j].d + h[j] - h[i];
					if (dd < 9000000)
						fprintf(fp, "        %d)\n", dd);
					else
						fprintf(fp, "        没有路径可达，无穷大)\n");
				}
			}
		}
	}
}



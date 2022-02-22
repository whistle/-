#define RE 1
#define BL 0
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h> 
using namespace std;

typedef struct in {
	int low;
	int high;
}interval;

typedef struct tt {
	in inin;
	bool color;
	int max;
	struct tt* left;
	struct tt* right;
	struct tt* p;
}tt, * pt;

typedef struct TT {		
	pt root;
	pt nil;
}TT, * T;
void left_rotate(T t, pt x);
void right_rotate(T t, pt x);
void rb_insert_fixup(T t, pt z);
void rb_insert(T t, pt z);
pt tree_minimun(T t, pt x);
void rb_transplant(T t, pt u, pt v);
void rb_delete_fixup(T t, pt x);
void rb_delete(T t, pt z); 
void mantain_max(T t, pt x);
void inorder_tree_walk(T t, pt x, FILE* fp);
pt interval_search(T t, in i);

int main() {
	int i, j, h;
	int ii[3];
	bool flag[30];
	T t = NULL;
	pt z = NULL;
	pt no[3];
	in ss[3];
	FILE* fp, * fo, * fi, * fu;
	fp = fopen("input.txt", "r");
	fo = fopen("inorder.txt", "w");
	fi = fopen("delete_data.txt", "w");
	fu = fopen("search.txt", "w");
	t = (T)malloc(sizeof(TT));					
	t->nil = (pt)malloc(sizeof(tt));				
	t->nil->color = BL;
	t->nil->left = t->nil->p = t->nil->right = t->nil;
	t->nil->max = 0;
	z = (pt)malloc(sizeof(tt));
	fscanf(fp, "%d", &(z->inin.low));
	fscanf(fp, "%d", &(z->inin.high));
	z->color = BL;
	z->left = t->nil;
	z->right = t->nil;
	z->p = t->nil;
	t->root = z;
	memset(ii, -1, 12);
	memset(flag, 0, 30 * sizeof(bool));
	srand((unsigned)time(0));
	for (i = 0; i < 3;) {
		h = rand() % (30) + 0;
		for (j = 0; j <= i; j++) {
			if (j == i) {
				ii[i] = h;
				i++;
			}
			if (ii[j] == h)
				break;
		}
	}
	for (i = 0; i < 3; i++)
		flag[ii[i]] = 1;
	j = 0;
	if (flag[0] == 1) {
		no[j] = z;
		j++;
	}
	for (i = 1; i < 30; i++) {			
		z = (pt)malloc(sizeof(tt));
		fscanf(fp, "%d", &(z->inin.low));
		fscanf(fp, "%d", &(z->inin.high));
		rb_insert(t, z);
		if (flag[i] == 1) {
			no[j] = z;
			j++;
		}
	}
	mantain_max(t, t->root);
	inorder_tree_walk(t, t->root, fo);
	fprintf(fo, "\n");
	for (i = 0; i < 3; i++)
		rb_delete(t, no[i]);
	mantain_max(t, t->root);
	fprintf(fi, "É¾³ý\n");
	for (i = 0; i < 3; i++)
		fprintf(fi, "%d %d %d\n", no[i]->inin.low, no[i]->inin.high, no[i]->max);
	fprintf(fi, "É¾³ýÖ®ºó\n");
	inorder_tree_walk(t, t->root, fi);
	pt x;
	h = rand() % (25) + 0;
	ss[0].low = h;
	while (h <= ss[0].low)
		h = rand() % (25) + 1;
	ss[0].high = h;
	for (i = 1; i < 3; i++) {
		h = rand() % (20) + 30;
		ss[i].low = h;
		while (h <= ss[i].low)
			h = rand() % (20) + 31;
		ss[i].high = h;
	}
	for (i = 0; i < 3; i++) {
		fprintf(fu, "%d %d\n", ss[i].low, ss[i].high);
		x = interval_search(t, ss[i]);
		if (x != t->nil)
			fprintf(fu, "x=%d %d\n", x->inin.low, x->inin.high);
		else
			fprintf(fu, "NULL\n");
		fprintf(fu, "\n");
	}
	free(t);
	free(z);
	fclose(fp);
	fclose(fo);
	fclose(fi);
	fclose(fu);
}

void left_rotate(T t, pt x) {				
	if (x->right == t->nil)
		return;
	pt y;
	y = x->right;
	x->right = y->left;
	if (y->left != t->nil)
		y->left->p = x;
	y->p = x->p;
	if (x->p == t->nil)
		t->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else x->p->right = y;
	y->left = x;
	x->p = y;
}

void right_rotate(T t, pt x) {				
	if (x->left == t->nil)
		return;
	pt y;
	y = x->left;
	x->left = y->right;
	if (y->right != t->nil)
		y->right->p = x;
	y->p = x->p;
	if (x->p == t->nil)
		t->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else x->p->right = y;
	y->right = x;
	x->p = y;
}

void rb_insert_fixup(T t, pt z) {			
	pt y;
	while (z->p->color == RE) {
		if (z->p == z->p->p->left) {
			y = z->p->p->right;
			if (y->color == RE) {
				z->p->color = BL;				//case 1
				y->color = BL;					//case 1
				z->p->p->color = RE;				//case 1
				z = z->p->p;						//case 1
			}
			else {
				if (z == z->p->right) {
					z = z->p;						//case 2
					left_rotate(t, z);				//case 2
				}
				z->p->color = BL;				//case 3
				z->p->p->color = RE;				//case 3
				right_rotate(t, z->p->p);			//case 3
			}
		}
		else {
			y = z->p->p->left;
			if (y->color == RE) {
				z->p->color = BL;				//case 1
				y->color = BL;					//case 1
				z->p->p->color = RE;				//case 1
				z = z->p->p;						//case 1
			}
			else {
				if (z == z->p->left) {
					z = z->p;						//case 2
					right_rotate(t, z);				//case 2
				}
				z->p->color = BL;				//case 3
				z->p->p->color = RE;				//case 3
				left_rotate(t, z->p->p);			//case 3
			}
		}
		t->root->color = BL;
	}
}

void rb_insert(T t, pt z) {			
	pt x, y;
	y = t->nil;
	x = t->root;
	while (x != t->nil) {
		y = x;
		if (z->inin.low < x->inin.low)
			x = x->left;
		else x = x->right;
	}
	z->p = y;
	if (y == t->nil)
		t->root = z;
	else if (z->inin.low < y->inin.low)
		y->left = z;
	else y->right = z;
	z->left = t->nil;
	z->right = t->nil;
	z->color = RE;
	rb_insert_fixup(t, z);
}

pt tree_minimun(T t, pt x) {				
	while (x->left != t->nil)
		x = x->left;
	return x;
}

void rb_transplant(T t, pt u, pt v) {		
	if (u->p == t->nil)
		t->root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else u->p->right = v;
	v->p = u->p;
}

void rb_delete_fixup(T t, pt x) {			 
	pt w;
	while (x != t->root && x->color == BL) {
		if (x == x->p->left) {
			w = x->p->right;
			if (w->color == RE) {
				w->color = BL;					//case 1
				x->p->color = RE;					//case 1
				left_rotate(t, x->p);				//case 1
				w = x->p->right;					//case 1
			}
			if (w->left->color == BL && w->right->color == BL) {
				w->color = RE;						//case 2
				x = x->p;							//case 2
			}
			else {
				if (w->right->color == BL) {
					w->left->color = BL;			//case 3
					w->color = RE;					//case 3
					right_rotate(t, w);				//case 3
					w = x->p->right;				//case 3
				}
				w->color = x->p->color;				//case 4
				x->p->color = BL;				//case 4
				w->right->color = BL;			//case 4
				left_rotate(t, x->p);				//case 4
				x = t->root;						//case 4
			}
		}
		else {
			w = x->p->left;
			if (w->color == RE) {
				w->color = BL;					//case 1
				x->p->color = RE;					//case 1
				right_rotate(t, x->p);				//case 1
				w = x->p->left;						//case 1
			}
			if (w->right->color == BL && w->left->color == BL) {
				w->color = RE;						//case 2
				x = x->p;							//case 2
			}
			else {
				if (w->left->color == BL) {
					w->right->color = BL;		//case 3
					w->color = RE;					//case 3
					left_rotate(t, w);				//case 3
					w = x->p->left;					//case 3
				}
				w->color = x->p->color;				//case 4
				x->p->color = BL;				//case 4
				w->left->color = BL;				//case 4
				right_rotate(t, x->p);				//case 4
				x = t->root;						//case 4
			}
		}
	}
	x->color = BL;
}

void rb_delete(T t, pt z) {				 
	pt x, y;
	y = z;
	bool y_original_color = y->color;
	if (z->left == t->nil) {
		x = z->right;
		rb_transplant(t, z, z->right);
	}
	else if (z->right == t->nil) {
		x = z->left;
		rb_transplant(t, z, z->left);
	}
	else {
		y = tree_minimun(t, z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->p == z)
			x->p = y;
		else {
			rb_transplant(t, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		rb_transplant(t, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if (y_original_color == BL)
		rb_delete_fixup(t, x);
}

void mantain_max(T t, pt x) {
	if (x != t->nil) {
		mantain_max(t, x->left);
		mantain_max(t, x->right);
		x->max = x->left->max;
		if (x->max < x->right->max)
			x->max = x->right->max;
		if (x->max < x->inin.high)
			x->max = x->inin.high;
	}
}

void inorder_tree_walk(T t, pt x, FILE* fp) {
	if (x != t->nil) {
		inorder_tree_walk(t, x->left, fp);
		fprintf(fp, "%d %d %d\n", x->inin.low, x->inin.high, x->max);
		inorder_tree_walk(t, x->right, fp);
	}
}


pt interval_search(T t, in i) {
	pt x = t->root;
	while (x != t->nil && (i.high < x->inin.low || x->inin.high < i.low)) {
		if (x->left != t->nil && x->left->max >= i.low)
			x = x->left;
		else x = x->right;
	}
	return x;
}





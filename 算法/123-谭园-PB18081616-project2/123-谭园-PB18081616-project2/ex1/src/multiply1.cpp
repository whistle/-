#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
void readinput(FILE *F,LONGLONG A[]);
void print_optimal_parens(int **s,int i,int j,FILE *R);
void print_store(LONGLONG **m,int **s);
void matrix_chain_order(LONGLONG *A,LONGLONG **m,int **s,int plength);
int mulsize[6]={0,6,11,16,21,26};
int main(){
    int i,j;
	int size;
	FILE *F,*R,*T;
	F=fopen("2_1_input.txt","r");
	R=fopen("result.txt","w");
	T=fopen("time.txt","w");
	double run_time;
	_LARGE_INTEGER time_start;	//开始	
	_LARGE_INTEGER time_over; 	//结束	
	double dqFreq;					
	LARGE_INTEGER f;                
	QueryPerformanceFrequency(&f);
	dqFreq=(double) f.QuadPart;
    for(i=1;i<=5;i++){
        LONGLONG *A,**m;
		int **s;
		A=( LONGLONG*)malloc(sizeof(LONGLONG)*mulsize[i]);
		readinput(F,A);
        m=(LONGLONG**)malloc(sizeof(LONGLONG*)*mulsize[i]);
		for(j=0;j<mulsize[i];j++)  m[j]=(LONGLONG*)malloc(sizeof(LONGLONG)*mulsize[i]);
		s=(int**)malloc(sizeof(int*)*(mulsize[i]-1));  
		for(j=0;j<mulsize[i]-1;j++)  s[j]=(int*)malloc(sizeof(int)*mulsize[i]);
		QueryPerformanceCounter(&time_start);
        matrix_chain_order(A,m,s,mulsize[i]);
		QueryPerformanceCounter(&time_over);
		run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
		fprintf(R,"min multipul		%lld\nmy plan		",m[1][mulsize[i]-1]);
		print_optimal_parens(s,1,mulsize[i]-1,R);
		fprintf(R,"\n");
		fprintf(T,"run_time	%lf	us\n",run_time);
        if(i==1) print_store(m,s);
	}
	fclose(F);
	fclose(R);
	fclose(T);
    system("pause");
    return 0;
}

//读入 
void readinput(FILE *f,LONGLONG A[]){
	int size;
	fscanf(f,"%d",&size);
	size++;
	for(int i=0;i<size;i++) fscanf(f,"%lld",&A[i]);
}

//矩阵链乘动态规划算法
void matrix_chain_order(LONGLONG *A,LONGLONG **m,int **s,int plength){
	int n=plength-1;
	int i,j,k,l;
	LONGLONG q;
	for (i=1;i<=n;i++) m[i][i]=0;
	for (l=2;l<=n;l++){
		for(i=1;i<=n-l+1;i++){
			j=i+l-1;
			m[i][j]= MAXLONGLONG;
			for(k=i;k<=j-1;k++){
				q=m[i][k]+m[k+1][j]+A[i-1]*A[k]*A[j];
				if (q<m[i][j]){
					m[i][j]=q;
					s[i][j]=k;
				}
			}
		}
	}
}

//输出 
void print_optimal_parens(int **s,int i,int j,FILE *f){
	if (i==j) fprintf(f,"A%d",i);
	else{
		fprintf(f,"(");
		print_optimal_parens(s,i,s[i][j],f);
		print_optimal_parens(s,s[i][j]+1,j,f);
		fprintf(f,")");
	}
}

void print_store(LONGLONG **m,int **s){
    int i,j;
    printf("m    row from 1 to 5,column from 5 to 1\n");
    for(i=1;i<=5;i++){
        for(j=5;j>=i;j--){
            printf("%lld  ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\ns  row from 1 to 4,column from 5 to 2\n");
    for(i=1;i<=4;i++){
        for(j=5;j>=(1+i);j--){
            printf("%d  ",s[i][j]);
        }
        printf("\n");
    }
}



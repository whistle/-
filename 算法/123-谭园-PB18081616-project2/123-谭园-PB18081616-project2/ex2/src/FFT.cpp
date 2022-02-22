#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
int polysize[7]={0,8,16,32,64,128,256};
struct complex{
	double real;
	double imag;
};
complex add(complex a,complex b);//复数加法 
complex sub(complex a,complex b);//复数减法
complex mul(complex a,complex b);//复数乘法 
void readinput(FILE *F,complex A[]); 
complex* RECURSIVE_FFT(complex *A,int n);//递归FFT 
void print_result(FILE *R,complex A[],int size);//打印结果 
void print(complex A[]);
int main(){
	int i;
	FILE *F,*R,*T;
	F=fopen("2_2_input.txt","r");
	R=fopen("result.txt","w");
	T=fopen("time.txt","w");
	double run_time;
	_LARGE_INTEGER time_start;		// 开始 
	_LARGE_INTEGER time_over; 		//结束 
	double dqFreq;					
	LARGE_INTEGER f;                
	QueryPerformanceFrequency(&f);
	dqFreq=(double) f.QuadPart;
	for(i=1;i<=6;i++){
		complex *A,*B;
		A=(complex *)malloc(sizeof(complex)*polysize[i]);
		readinput(F,A);
		QueryPerformanceCounter(&time_start);
		B=RECURSIVE_FFT(A,polysize[i]);
		QueryPerformanceCounter(&time_over);
		run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
		fprintf(T,"run_time	%lf	us\n",run_time);
		print_result(R,B,polysize[i]);
		if(i==1) print(B);
	}
	fclose(F);
	fclose(R);
	fclose(T);	
    
    return 0;
}
complex add(complex a,complex b){
	complex c;
	c.real=a.real+b.real;
	c.imag=a.imag+b.imag;
	return c;
}

complex sub(complex a,complex b){
	complex c;
	c.real=a.real-b.real;
	c.imag=a.imag-b.imag;
	return c;
}

complex mul(complex a,complex b){
	complex c;
	c.real=a.real*b.real-a.imag*b.imag;
	c.imag=a.imag*b.real+a.real*b.imag;
	return c;
}

void readinput(FILE *F,complex A[]){
	int i,size;
	fscanf(F,"%d",&size);
	for(i=0;i<size;i++) fscanf(F,"%lf",&A[i].real);
	for(i=0;i<size;i++) A[i].imag=0;
}

complex* RECURSIVE_FFT(complex *A,int n){
	if(n==1) return A;
	complex w,wn;
	w.real=1;
	w.imag=0;
	wn.real=cos(2*M_PI/n);
	wn.imag=sin(2*M_PI/n);
	complex *A0,*A1;
	A0=(complex *)malloc(sizeof(complex)*(n/2));
	A1=(complex *)malloc(sizeof(complex)*(n/2));
	int i;
	for(i=0;i<n;i++){
		if(i%2==0) A0[i/2]=A[i];
		else       A1[i/2]=A[i];
	}
	complex *Y0,*Y1;
	Y0=RECURSIVE_FFT(A0,n/2);
	Y1=RECURSIVE_FFT(A1,n/2);
	complex *Y;
	Y=(complex *)malloc(sizeof(complex)*n);
	for(i=0;i<n/2;i++){
		Y[i]=add(Y0[i],mul(w,Y1[i]));
		Y[i+n/2]=sub(Y0[i],mul(w,Y1[i]));
		w=mul(w,wn);
	}
	return Y;
}

void print_result(FILE *R,complex A[],int size){
	fprintf(R,"%d\n",size);
	for(int i=0;i<size;i++)		fprintf(R,"%lf	",A[i].real);
	fprintf(R,"\n");
}

void print(complex A[]){
	for(int i=0;i<8;i++){ 
	printf("{%lf,%lf}	",A[i].real,A[i].imag);
	printf("\n") ;
	} 
}



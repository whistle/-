#include<stdio.h>
#include<string.h>
#include<time.h>
#include<math.h> 
#include<stdlib.h>
#include<windows.h>
void swap(int* a, int*b);
int hoareway(int* src, int start, int end);
void dealquicksort(int *src, int start, int end);
void quicksort(int *src, int n);//���� 
void dealMergeSort(int *src, int* tmp, int  str, int  end);
void MergeSort(int *src, int n);//�鲢 
void HeapAdjust(int arr[], int i, int length);
void InsertSort(int arr[], int length);//���� 
void HeapSort(int arr[], int length);//�� 
void counting_sort(int arr[], int n,int k);//�������� 
int main()
{
	//��ȡ����ʱ�� 
	clock_t begin,end;
	double runtime;
	_LARGE_INTEGER time_start;	//��ʼʱ��
	_LARGE_INTEGER time_over;	//����ʱ��
	double dqFreq;		//��ʱ��Ƶ��
	LARGE_INTEGER f;	//��ʱ��Ƶ��
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart; 
	
	int x=3;
	int k=pow(2,x);//�����ģ 
	int a[k]={0};
	int b[k]={0}; 
	int c[k]={0};//�������� 
	FILE *fp=fopen("input.txt","r");
	if(fp==NULL)
	{
		return 0;
	}
	for(int i=0;i<k;i++)
	{
		fscanf(fp,"%d ",&a[i]);
	}
	fclose(fp);
	
	for(int i=0;i<k;i++) b[i]=a[i];
	QueryPerformanceCounter(&time_start);//��ʼ��ʱ 
	InsertSort(b,k);
	QueryPerformanceCounter(&time_over);//������ʱ 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	printf("\n��������ʱ���ǣ�%fus\n",runtime);
	fp=fopen("result_3.txt","w+");   //���ļ�
	if(fp!=NULL)
		for(int i=0;i<k;i++)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);
	
	for(int i=0;i<k;i++) b[i]=a[i];
	QueryPerformanceCounter(&time_start);//��ʼ��ʱ 
	HeapSort(b,k);
	QueryPerformanceCounter(&time_over);//������ʱ 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	printf("\n�Ѳ�������ʱ���ǣ�%fus\n",runtime);
		fp=fopen("Heap_result_3.txt","w+");   //���ļ�
	if(fp!=NULL)
		for(int i=0;i<k;i++)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);

	for(int i=0;i<k;i++) b[i]=a[i];
	QueryPerformanceCounter(&time_start);//��ʼ��ʱ 
	quicksort(b, k);
	QueryPerformanceCounter(&time_over);//������ʱ 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;//����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000 000/��cpu��Ƶ��΢��
	printf("\n��������ʱ���ǣ�%fus\n",runtime);	
		fp=fopen("QUICK_result_3.txt","w+");   //���ļ�
	if(fp!=NULL)
		for(int i=0;i<k;i++)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);

	for(int i=0;i<k;i++) b[i]=a[i];
	QueryPerformanceCounter(&time_start);//��ʼ��ʱ 
	MergeSort(b, k);
	QueryPerformanceCounter(&time_over);//������ʱ 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;//����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000 000/��cpu��Ƶ��΢��
	printf("\n�鲢����ʱ���ǣ�%fus\n",runtime);
		fp=fopen("Mergeresult_3.txt","w+");   //���ļ�
	if(fp!=NULL)
		for(int i=k-1;i>=0;i--)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);
	//	for(int i=0;i<k;i++) printf("%d\n",b[i]);
	
	for(int i=0;i<k;i++) b[i]=a[i];
	QueryPerformanceCounter(&time_start);//��ʼ��ʱ 
	counting_sort(b,k,32768);
	QueryPerformanceCounter(&time_over);//������ʱ 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;//����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000 000/��cpu��Ƶ��΢��
	printf("\n��������ʱ���ǣ�%fus\n",runtime);
		fp=fopen("CT_result_3.txt","w+");   //���ļ�
	if(fp!=NULL)
		for(int i=0;i<k;i++)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);
	//for(int i=0;i<k;i++) printf("%d\n",b[i]);
	
	return 1;
}

// ��������
void InsertSort(int arr[], int length)
{
	for (int i = 1; i < length; i++)
	{
		int j;
		if (arr[i] < arr[i - 1])
		{
			int temp = arr[i];
			for (j = i - 1; j >= 0 && temp < arr[j]; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}
}
// ��������
void swap(int* a, int*b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
int hoareway(int* src, int start, int end)
{
	int a = start + 1, b = end - 2;
	int mid = (start + end) / 2;
	if (src[start] > src[mid])
	{
		swap(src + start, src + mid);
	}
	if (src[mid] > src[end])
	{
		swap(src + mid, src + end);
	}
	if (src[start] > src[mid])
	{
		swap(src + start, src + mid);
		/*�������������򲿷�*/
	}
	if (end - mid <= 2)
	{
		return mid;
		/*���С��4����ֱ�ӷ������*/
	}
	/*������׼ֵ*/
	swap(src + mid, src + end - 1);
	while (a <= b)
	{
		while (a < end - 1 && src[a] <= src[end - 1])
		{
 
			a++;
		}
		while (b > 0 && src[b] >= src[end - 1])
		{
			b--;
 
		}
		if (a == b && (a == 1 || a == end - 1))
		{
			break;
			/*һ�����ҵ�ͬһ��ֵ��һ�����ҵ����Ѿ������źõĵط�����ʱ�Ͳ�����*/
		}
		if (a < b)
		{
			swap(src + a, src + b);
			/* ����*/
		}
 
	}
	swap(src + a, src + end - 1);//����׼ֵ��������
	return a;
}
 
void dealquicksort(int *src, int start, int end)
{
	int mid;
	if (start < end)
	{
		mid = hoareway(src, start, end);
		dealquicksort(src, start, mid - 1);
		dealquicksort(src, mid + 1, end);
	}
}
void quicksort(int *src, int n)
{
	//��������
	dealquicksort(src, 0, n - 1);
}
void dealMergeSort(int *src, int* tmp, int  str, int  end)
{
	if (str >= end)
	{
		return;
 
	}
	int mid = (str + end) / 2;
	dealMergeSort(src, tmp, str, mid);
	dealMergeSort(src, tmp, mid + 1, end);
	int a = str;
	int b = mid + 1;
	int c = str;//1,5,6,15,8,26,5,55,9,0 
	while (a <= mid && b <= end)
	{
 
		if (src[a] > src[b])
		{
			tmp[c] = src[a];
			a++;
		}
		else
		{
			tmp[c] = src[b];
			b++;
		}
		c++;
	//�������Ѿ��ȽϺõ����ݴ�����ʱ�Ŀռ�����
	}
	for (; a <= mid; a++, c++)
	{
		tmp[c] = src[a];
	}
	for (; b <= end; b++, c++)
	{
		tmp[c] = src[b];
	}
	//��ʣ������ݴ浽��ʱ��������
	int i = 0;
	for (i = 0; i <= end; ++i)
	{
		src[i] = tmp[i];
	}
	//����ʱ����Ԫ�ش��뵽ԭ���鵱��
}
void MergeSort(int *src, int n)
{
	int *tmp = (int*)malloc(n * sizeof(int));
	dealMergeSort(src, tmp, 0, n - 1);//�����±�
	free(tmp);
}	
/*
	@param arr ������������
	@param i �������Ľ����±�
	@param length ����ĳ���
*/
void HeapAdjust(int arr[], int i, int length)
{
	// ����iλ�õĽ��
	// �ȱ��浱ǰ�����±�
	int max = i;
	// ��ǰ������Һ��ӽ����±�
	int lchild = i * 2 + 1;
	int rchild = i * 2 + 2;
	if (lchild < length && arr[lchild] > arr[max])
	{
		max = lchild;
	}
	if (rchild < length && arr[rchild] > arr[max])
	{
		max = rchild;
	}
	// ��i����ֵ�������Һ��ӽ���ֵС���ͽ�������ֵ���н���
	if (max != i)
	{
		int temp;
		temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;
		// �ݹ�
		HeapAdjust(arr, max, length);
	}
}
 
// ������
void HeapSort(int arr[], int length)
{
	// ��ʼ����
	// length / 2 - 1�Ƕ����������һ����Ҷ�ӽ������
	for (int i = length / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(arr, i, length);
	}
	// �����Ѷ�Ԫ�غ����һ��Ԫ��
	for (int i = length - 1; i >= 0; i--)
	{
		int temp;
		temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		HeapAdjust(arr, 0, i);
	}
}
//��������
void counting_sort(int arr[], int n,int k)
{
  int *c, *b;
  int i;
  c = (int *)malloc(sizeof(int)*k);/*��ʱ����,ע�����Ĵ�С�Ǵ�����������ֵ�����Ǹ�����ٶ����������������ֵΪ1000000�����������Ҫ1000000*sizeof(int)���洢��Ԫ*/
  b = (int *)malloc(sizeof(int)*n); /*���������������*/
  for (i = 0; i < k; i++)
    c[i] = 0;  /*��ʼ��*/
  for (i = 0; i < n; i++)
    c[arr[i]] += 1; /*ͳ������arr��ÿ��ֵΪi��Ԫ�س��ֵĴ���*/
  for (i = 1; i < k; i++)
   c[i] = c[i - 1] + c[i];     /*ȷ��ֵΪi��Ԫ��������c�г��ֵ�λ��*/
  for (i = n - 1; i >= 0; i--)
  {
    b[c[arr[i]] - 1] = arr[i]; /*��arr���飬�Ӻ���ǰȷ��ÿ��Ԫ�����ڵ�����λ��;*/
    c[arr[i]] -= 1;
  }
  for (i = 0; i < n; i++)
    arr[i] = b[i];/*���Ŀ���Ƿ���arr������Ϊ��������*/
  free(c);
  free(b);
}

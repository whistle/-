#include<stdio.h>
#include<string.h>
#include<time.h>
#include<math.h> 
#include<stdlib.h>
#include<windows.h>
void swap(int* a, int*b);
int hoareway(int* src, int start, int end);
void dealquicksort(int *src, int start, int end);
void quicksort(int *src, int n);//快排 
void dealMergeSort(int *src, int* tmp, int  str, int  end);
void MergeSort(int *src, int n);//归并 
void HeapAdjust(int arr[], int i, int length);
void InsertSort(int arr[], int length);//插入 
void HeapSort(int arr[], int length);//堆 
void counting_sort(int arr[], int n,int k);//计数排序 
int main()
{
	//获取运行时间 
	clock_t begin,end;
	double runtime;
	_LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart; 
	
	int x=3;
	int k=pow(2,x);//排序规模 
	int a[k]={0};
	int b[k]={0}; 
	int c[k]={0};//辅助数组 
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
	QueryPerformanceCounter(&time_start);//开始计时 
	InsertSort(b,k);
	QueryPerformanceCounter(&time_over);//结束计时 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	printf("\n插入排序时间是：%fus\n",runtime);
	fp=fopen("result_3.txt","w+");   //打开文件
	if(fp!=NULL)
		for(int i=0;i<k;i++)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);
	
	for(int i=0;i<k;i++) b[i]=a[i];
	QueryPerformanceCounter(&time_start);//开始计时 
	HeapSort(b,k);
	QueryPerformanceCounter(&time_over);//结束计时 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	printf("\n堆插入排序时间是：%fus\n",runtime);
		fp=fopen("Heap_result_3.txt","w+");   //打开文件
	if(fp!=NULL)
		for(int i=0;i<k;i++)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);

	for(int i=0;i<k;i++) b[i]=a[i];
	QueryPerformanceCounter(&time_start);//开始计时 
	quicksort(b, k);
	QueryPerformanceCounter(&time_over);//结束计时 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\n快速排序时间是：%fus\n",runtime);	
		fp=fopen("QUICK_result_3.txt","w+");   //打开文件
	if(fp!=NULL)
		for(int i=0;i<k;i++)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);

	for(int i=0;i<k;i++) b[i]=a[i];
	QueryPerformanceCounter(&time_start);//开始计时 
	MergeSort(b, k);
	QueryPerformanceCounter(&time_over);//结束计时 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\n归并排序时间是：%fus\n",runtime);
		fp=fopen("Mergeresult_3.txt","w+");   //打开文件
	if(fp!=NULL)
		for(int i=k-1;i>=0;i--)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);
	//	for(int i=0;i<k;i++) printf("%d\n",b[i]);
	
	for(int i=0;i<k;i++) b[i]=a[i];
	QueryPerformanceCounter(&time_start);//开始计时 
	counting_sort(b,k,32768);
	QueryPerformanceCounter(&time_over);//结束计时 
	runtime=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\n计数排序时间是：%fus\n",runtime);
		fp=fopen("CT_result_3.txt","w+");   //打开文件
	if(fp!=NULL)
		for(int i=0;i<k;i++)		
			fprintf(fp,"%d\n",b[i]);	
	else
		printf("error");
	fclose(fp);
	//for(int i=0;i<k;i++) printf("%d\n",b[i]);
	
	return 1;
}

// 插入排序
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
// 快速排序
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
		/*上面是三数排序部分*/
	}
	if (end - mid <= 2)
	{
		return mid;
		/*如果小于4个数直接返回输出*/
	}
	/*保护基准值*/
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
			/*一种是找到同一个值，一种是找到了已经三数排好的地方，此时就不用排*/
		}
		if (a < b)
		{
			swap(src + a, src + b);
			/* 交换*/
		}
 
	}
	swap(src + a, src + end - 1);//将基准值交换回来
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
	//快速排序
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
	//将两个已经比较好的数据存入临时的空间里面
	}
	for (; a <= mid; a++, c++)
	{
		tmp[c] = src[a];
	}
	for (; b <= end; b++, c++)
	{
		tmp[c] = src[b];
	}
	//将剩余的数据存到临时数组里面
	int i = 0;
	for (i = 0; i <= end; ++i)
	{
		src[i] = tmp[i];
	}
	//将临时数组元素存入到原数组当中
}
void MergeSort(int *src, int n)
{
	int *tmp = (int*)malloc(n * sizeof(int));
	dealMergeSort(src, tmp, 0, n - 1);//传入下标
	free(tmp);
}	
/*
	@param arr 待调整的数组
	@param i 待调整的结点的下标
	@param length 数组的长度
*/
void HeapAdjust(int arr[], int i, int length)
{
	// 调整i位置的结点
	// 先保存当前结点的下标
	int max = i;
	// 当前结点左右孩子结点的下标
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
	// 若i处的值比其左右孩子结点的值小，就将其和最大值进行交换
	if (max != i)
	{
		int temp;
		temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;
		// 递归
		HeapAdjust(arr, max, length);
	}
}
 
// 堆排序
void HeapSort(int arr[], int length)
{
	// 初始化堆
	// length / 2 - 1是二叉树中最后一个非叶子结点的序号
	for (int i = length / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(arr, i, length);
	}
	// 交换堆顶元素和最后一个元素
	for (int i = length - 1; i >= 0; i--)
	{
		int temp;
		temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		HeapAdjust(arr, 0, i);
	}
}
//计数排序法
void counting_sort(int arr[], int n,int k)
{
  int *c, *b;
  int i;
  c = (int *)malloc(sizeof(int)*k);/*临时数组,注意它的大小是待排序序列中值最大的那个。如假定该排序序列中最大值为1000000，则该数组需要1000000*sizeof(int)个存储单元*/
  b = (int *)malloc(sizeof(int)*n); /*存放排序结果的数组*/
  for (i = 0; i < k; i++)
    c[i] = 0;  /*初始化*/
  for (i = 0; i < n; i++)
    c[arr[i]] += 1; /*统计数组arr中每个值为i的元素出现的次数*/
  for (i = 1; i < k; i++)
   c[i] = c[i - 1] + c[i];     /*确定值为i的元素在数组c中出现的位置*/
  for (i = n - 1; i >= 0; i--)
  {
    b[c[arr[i]] - 1] = arr[i]; /*对arr数组，从后向前确定每个元素所在的最终位置;*/
    c[arr[i]] -= 1;
  }
  for (i = 0; i < n; i++)
    arr[i] = b[i];/*这个目的是返回arr数组作为有序序列*/
  free(c);
  free(b);
}

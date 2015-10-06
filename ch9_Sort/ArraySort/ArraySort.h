#ifndef ARRAYSORT_H
#define ARRAYSORT_H

#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

template <typename T> void InsertSort(T *array, int n);
template <typename T> void ShellSort(T *array, int n);

template <typename T> void BoubbleSort(T *array, int n);
template <typename T> void BidBoubbleSort(T *array, int n);
template <typename T> void QuickSort(T *array, int n);
template <typename T> void FindNth(T *array, int n, int pos); //查找第pos个数字

template <typename T> void SelectSort(T *array, int n);
template <typename T> void HeapSort(T *array, int n);

template <typename T> void MergeSort(T *array, int n);
template <typename T> void RadixSort(T *array, int n);
template <typename T> void CountSort(T *array, int n);

template <typename T>
void InsertSort(T *array, int n)
{
	for ( int i = 1; i < n; i++ )
	{
		T tmp = array[i];
		for ( int j = i - 1; j >= 0 && array[j] > tmp; j-- )
			array[j + 1] = array[j];
		array[j + 1] = tmp;
	}
}

template <typename T>
void ShellSort(T *array, int n)
{
	for ( int step = n / 2; step > 0; step /= 2)
	{
		//注意此处的插入排序使用方法
		//尽管划分为n个序列
		//实际上按照物理序列遍历，逻辑上仍然按照多段处理
		for ( int i = step; i < n; i++ )
		{
			T tmp = array[i];
			for ( int j = i - step; j >= 0 && array[j] > tmp; j -= step )
				array[j + step] = array[j];
			array[j + step] = tmp;
		}
	}
}
/*
//设置boolean变量
template <typename T>
void BoubbleSort(T *array, int n)
{
	int exchange = 1;
	for ( int i = 1; i < n && exchange; i++ )
	{
		exchange = 0;
		for ( int j = n - 1; j >= i; j-- )
		{
			if ( array[j - 1] > array[j] )
			{
				T tmp = array[j - 1]; array[j - 1] = array[j]; array[j] = tmp;
				exchange = 1;
			}
		}
	}
}
*/
//记录有序位置
template <typename T>
void BoubbleSort(T *array, int n)
{
	int left = 1;
	for ( int i = 1; i < n && left != n - 1; i++ )
	{
		int exchange = n - 1;
		for ( int j = n - 1; j >= left; j-- )
		{
			if ( array[j - 1] > array[j] )
			{
				T tmp = array[j - 1]; array[j - 1] = array[j]; array[j] = tmp;
				exchange = j;
			}
		}
		left = exchange;
	}
}

template <typename T> 
void BidBoubbleSort(T *array, int n)
{
	int low = 0, high = n - 1;
	while ( low < high )
	{
		int exchange = high;
		for ( int i = low; i < high; i++ )
		{
			if ( array[i] > array[i + 1] )
			{
				T tmp = array[i]; array[i] = array[i + 1]; array[i + 1] = tmp;
				exchange = i;
			}
		}
		high = exchange;

		for ( i = high; i > low; i-- )
		{
			if ( array[i] < array[i - 1] )
			{
				T tmp = array[i]; array[i] = array[i - 1]; array[i - 1] = tmp;
				exchange = i;
			}
		}
		low = exchange;
	}
}

template <typename T>
void QuickSort(T *array, int left, int right)
{
	if ( left >= right )
		return ;

	int piovt = Partition(array, left, right);
	QuickSort(array, left, piovt - 1);
	QuickSort(array, piovt + 1, right);
}

template <typename T>
int Partition(T *array, int left, int right)
{
	int i = left, j = right;
	T tmp = array[i];

	while ( i < j )
	{
		while ( i < j && array[j] >= tmp )
			j--;
		if ( array[j] < array[i] )
			array[i] = array[j], i++;

		while ( i < j && array[i] <= tmp )
			i++;
		if ( array[i] > array[j] )
			array[j] = array[i], j--;
	}

	array[i] = tmp;
	return i;
}

template <typename T>
void QuickSort(T *array, int n)
{
	QuickSort(array, 0, n - 1);
}

template <typename T>
void FindNth(T *array, int left, int right, int pos) //返回索引
{
	if ( left > right )
		return ;
	
	int pivot = Partition(array, left, right);
	if ( pivot == pos - 1)
		return ;
	else if ( pivot < pos - 1)
		FindNth(array, pivot + 1, right, pos);
	else
		FindNth(array, left, pivot - 1, pos);
}

template <typename T> 
void FindNth(T *array, int n, int pos)
{
	FindNth(array, 0, n - 1, pos);
	cout << "第" << pos << "个数是：" << array[pos - 1] << endl;
}

template <typename T> 
void SelectSort(T *array, int n)
{
	for ( int i = 1; i < n; i++ )
	{
		int max = 0;
		for ( int j = 1; j <= n - i; j++ )
			if ( array[max] < array[j] )
				max = j;

		if ( max != n - i )
		{
			T tmp = array[max];
			array[max] = array[n - i];
			array[n - i] = tmp;
		}
	}
}

template <typename T>
void ShiftDown(T *array, int n, int pos)
{
	T tmp = array[pos];
	int child = 2 * pos + 1;

	while ( child < n )
	{
		if ( child + 1 < n && array[child] < array[child + 1] )
			child = child + 1;

		if ( tmp >= array[child] )
			break ;
		else
		{
			array[pos] = array[child];
			pos = child;
			child = 2 * pos + 1;
		}
	}

	array[pos] = tmp;
}

//大根堆
template <typename T> 
void HeapSort(T *array, int n)
{
	//初始化
	for ( int i = (n - 2) / 2; i >= 0; i-- )
		ShiftDown<T>(array, n, i);

	//筛选
	for ( i = 1; i < n; i++ )
	{
		T tmp = array[0]; array[0] = array[n - i]; array[n - i] = tmp;
		ShiftDown(array, n - i, 0);
	}
}

template <typename T>
void Merge(T *array, int begin, int mid, int end)
{
	T *src = new T[end + 1];
	assert( src );
	for ( int index = begin; index <= end; index++ )
		src[index] = array[index];

	int i = begin, j = mid + 1, k = begin;
	while ( i <= mid && j <= end )
	{
		if ( src[i] < src[j] )
			array[k++] = src[i++];
		else
			array[k++] = src[j++];
	}

	while ( i <= mid )
		array[k++] = src[i++];

	while ( j <= end )
		array[k++] = src[j++];
}

template <typename T> 
void MergeSort(T *array, int begin, int end)
{
	if ( begin >= end )
		return ;

	int tmp = (begin + end) / 2;
	MergeSort(array, begin, (begin + end) / 2 );
	MergeSort(array, (begin + end) / 2 + 1, end);
	Merge(array, begin, (begin + end) / 2,  end);
}

template <typename T>
void MergeSort(T *array, int n)
{
	MergeSort(array, 0, n - 1);
}

const int Radix = 10; //十进制的基数排序

template <typename T>
struct RadixNode
{
	T data;
	RadixNode<T> *next;

	RadixNode(T val, RadixNode<T> *p = NULL) : data( val ), next( p ) {}
};

template <typename T>
T getMaxNum(T *array, int n)
{
	T max = array[0];
	for ( int i = 1; i < n; i++ )
		if ( max < array[i] )
			max = array[i];
	return max;
}

template <typename T>
int getLoopTime(T num)
{
	int count = 0;
	while ( num != 0 )
	{
		count++;
		num /= Radix;
	}
	return count;
}

template <typename T>
void RadixSort(T *array, int n)
{
	//初始化数字序列
	RadixNode<T> *head = NULL, *tail = NULL;
	for ( int i = 0; i < n; i++ )
	{
		if ( head == NULL )
			head = tail = new RadixNode<T>(array[i], NULL);
		else
		{
			tail->next = new RadixNode<T>(array[i], NULL);
			tail = tail->next;
		}
	}
	RadixNode<T> ** front = new RadixNode<T> *[ Radix ];
	RadixNode<T> ** rear = new RadixNode<T> *[ Radix ];

	int Loop = getLoopTime( getMaxNum(array, n) );
	//循环
	for ( int loop = 0; loop < Loop; loop++ )
	{   //堆初始化
		for ( int i = 0; i < Radix; i++ )
			front[i] = rear[i] = NULL;
		//分配
		RadixNode<T> *p = head;
		while ( p )
		{	//关键字
			T key = (int)( p->data / pow(Radix, loop) ) % Radix;
			//存储，平移
			RadixNode<T> *tmp = p;
			p = p->next;
			//摘取并插入
			if ( front[key] == NULL )
				front[key] = rear[key] = tmp;
			else
			{
				rear[key]->next = tmp;
				rear[key] = rear[key]->next;
			}
			tmp->next = NULL;
		}
		//收集
		head = tail = NULL;
		for ( i = 0; i < Radix; i++ )
		{
			while ( i < Radix && front[i] == NULL )
				i++;
			if ( i == Radix )
				break;
				
			if ( head == NULL )
				head = front[i];
			else
				tail->next = front[i];

			tail = rear[i];
		}
	}
	//恢复
	int count = 0;
	for ( RadixNode<T> *p = head; p; )
	{
		array[count++] = p->data;

		RadixNode<T> *del = p;
		p = del->next;
		delete []del;
	}
}

template <typename T>
T Max(T *array, int n)
{
	T max = array[0];
	for ( int i = 1; i < n; i++ )
		if ( max < array[i] )
			max = array[i];
	return max;
}

template <typename T>
T Min(T *array, int n)
{
	T min = array[0];
	for ( int i = 1; i < n; i++ )
		if ( min > array[i] )
			min = array[i];
	return min;
}
/*
template <typename T>
void CountSort(T *array, int n)
{
	int k = Max(array, n); //数字的范围
	int *count = new int[ k + 1 ];
	assert( count );
	for ( int i = 0; i <= k; i++ )
		count[i] = 0;
	//计数
	for ( i = 0; i < n; i++ )
		count[ array[i] ]++;
	//算截止位置
	for ( i = 1; i <= k; i++ )
		count[i] += count[i - 1];
	//复制
	T *src = new T[n];
	for ( i = 0; i < n; i++ )
		src[i] = array[i];
	for ( i = 0; i < n; i++ )
		array[ --count[src[i]] ] = src[i];
}
*/
template <typename T>
void CountSort(T *array, int n)
{
	int k = Max(array, n); //数字的范围
	int *count = new int[ k + 1 ];
	assert( count );
	for ( int i = 0; i <= k; i++ )
		count[i] = 0;
	//计数
	for ( i = 0; i < n; i++ )
		count[ array[i] ]++;
	//排序
	int j = 0;
	for ( i = 0; i <= k; i++ )
	{
		while ( count[i] > 0 )
		{
			array[j++] = i;
			count[i]--;
		}
	}
}
#endif
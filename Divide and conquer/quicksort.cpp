#include<iostream>
#include<fstream>
#include<Windows.h>
constexpr auto MAX_LEN = 2000000;
using namespace std;
void read_file(int a[], string file_name);			 //读文件并处理
void out_file(int a[], string file_name, int number);/*将排序结果写入文件*/
void quick_sort(int a[], int left, int right);		 //快速排序

int main()
{
	int* sort_array = (int*)malloc(sizeof(int) * MAX_LEN);
	read_file(sort_array, "quicksort.in");
	free(sort_array);
	return 0;
}

//读文件并处理
void read_file(int a[], string file_name)
{
	int number = 0;
	fstream sortin;
	sortin.open(file_name, ios::in | ios::out);
	if (!sortin)
	{
		cout << "quicksort.in打开失败" << endl;
		exit(-1);
	}
	//读入文件第一行的数字
	sortin >> number;
	//存储待排序数字
	for (int i = 0; i < number; i++)
		sortin >> a[i];
	sortin.close();

	quick_sort(a, 0, number - 1);
	out_file(a, "quicksort.out", number);
}
//将排序结果写入文件
void out_file(int a[], string file_name, int number)
{
	ofstream outfile(file_name, ios::out | ios::trunc);
	if (!outfile.is_open())
	{
		cout << "quicksort.out打开失败" << endl;
		exit(1);
	}
	for (int i = 0; i < number; i++)
	{
		outfile << a[i] << " ";
		//printf("%d ", a[i]);
	}
	outfile.close();
}
//快排
void quick_sort(int a[], int left,int right)
{
	if(left<right)
	{
		//将首个数字作为flag_num
		int i = left, j = right, tmp = a[left];
		while(i<j)
		{
			//首先从右边界向左寻找
			while (i<j && a[j]>tmp)
				j--;
			if(i<j)
			{
				a[i] = a[j];
				i++;
			}

			while (i < j && a[i] <= tmp)
				i++;
			if(i<j)
			{
				a[j] = a[i];
				j--;
			}
		}
		/*进行到i==j时，将pivot置于中间。
		此时，左边均为小于tmp的值，右边均为大于tmp的值*/
		a[i] = tmp;
		quick_sort(a, left, i - 1);
		quick_sort(a, i + 1, right);
	}
}
#include<iostream>
#include<fstream>
constexpr auto MAX_LEN = 1000000;
using namespace std;
int min_n(int a, int b);//返回最小值
void read_file(int a[], string file_name);//读文件并处理
void out_file(int a[], string file_name, int number);/*将排序结果写入文件*/
void merge_sort(int a[], int len);//迭代法归并排序

int main()
{
	int* sort_array = (int*)malloc(sizeof(int) * MAX_LEN);
	read_file(sort_array, "mergesort.in");
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
		cout << "mergesort.in打开失败" << endl;
		exit(-1);
	}
	sortin >> number;
	for (int i = 0; i < number; i++)
		sortin >> a[i];
	sortin.close();
	merge_sort(a, number);
	out_file(a, "mergesort.out", number);
}
//将排序结果写入文件
void out_file(int a[], string file_name,int number)
{
	ofstream outfile(file_name, ios::in | ios::out | ios::trunc);
	if (!outfile.is_open())
	{
		cout << "mergesort.out打开失败" << endl;
		exit(1);
	}
	for (int i = 0; i < number; i++)
		outfile << a[i] << " ";
	outfile.close();
}
//迭代法归并排序
void merge_sort(int a[], int len)
{
	int* aux_array = (int*)malloc(sizeof(int) * len);
	//开始下标，步长
	int start = 0, step = 1;
	//左右边界及中间值
	int left = 0, mid = 0, right = 0;
	//两个子数组的边界
	int left1 = 0, left2 = 0, right1 = 0, right2 = 0;
	//辅助数组下标
	int k = start;
	for (step = 1; step < len; step *= 2)
	{
		for (start = 0; start < len; start += 2 * step)
		{
			left = start, k = start;
			mid = min_n(len, start + step);
			right = min_n(len, start + 2 * step);

			left1 = left, left2 = mid;
			right1 = mid, right2 = right;
			while (left1 < right1 && left2 < right2)
			{
				if (a[left1] < a[left2])
				{
					aux_array[k] = a[left1];
					k++, left1++;
				}
				else
				{
					aux_array[k] = a[left2];
					k++, left2++;
				}
			}
			/*将比较结束剩下的数写入辅助数组*/
			while (left1 < right1)
			{
				aux_array[k] = a[left1];
				k++, left1++;
			}
			while (left2 < right2)
			{
				aux_array[k] = a[left2];
				k++, left2++;
			}
		}
		for (int i = 0; i < right + 1; i++)
			a[i] = aux_array[i];
	}
	free(aux_array);
}
//返回最小值
int min_n(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

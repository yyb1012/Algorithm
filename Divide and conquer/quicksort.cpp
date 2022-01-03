#include<iostream>
#include<fstream>
#include<Windows.h>
constexpr auto MAX_LEN = 2000000;
using namespace std;
void read_file(int a[], string file_name);			 //���ļ�������
void out_file(int a[], string file_name, int number);/*��������д���ļ�*/
void quick_sort(int a[], int left, int right);		 //��������

int main()
{
	int* sort_array = (int*)malloc(sizeof(int) * MAX_LEN);
	read_file(sort_array, "quicksort.in");
	free(sort_array);
	return 0;
}

//���ļ�������
void read_file(int a[], string file_name)
{
	int number = 0;
	fstream sortin;
	sortin.open(file_name, ios::in | ios::out);
	if (!sortin)
	{
		cout << "quicksort.in��ʧ��" << endl;
		exit(-1);
	}
	//�����ļ���һ�е�����
	sortin >> number;
	//�洢����������
	for (int i = 0; i < number; i++)
		sortin >> a[i];
	sortin.close();

	quick_sort(a, 0, number - 1);
	out_file(a, "quicksort.out", number);
}
//��������д���ļ�
void out_file(int a[], string file_name, int number)
{
	ofstream outfile(file_name, ios::out | ios::trunc);
	if (!outfile.is_open())
	{
		cout << "quicksort.out��ʧ��" << endl;
		exit(1);
	}
	for (int i = 0; i < number; i++)
	{
		outfile << a[i] << " ";
		//printf("%d ", a[i]);
	}
	outfile.close();
}
//����
void quick_sort(int a[], int left,int right)
{
	if(left<right)
	{
		//���׸�������Ϊflag_num
		int i = left, j = right, tmp = a[left];
		while(i<j)
		{
			//���ȴ��ұ߽�����Ѱ��
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
		/*���е�i==jʱ����pivot�����м䡣
		��ʱ����߾�ΪС��tmp��ֵ���ұ߾�Ϊ����tmp��ֵ*/
		a[i] = tmp;
		quick_sort(a, left, i - 1);
		quick_sort(a, i + 1, right);
	}
}
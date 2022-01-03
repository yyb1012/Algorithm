#include<iostream> 
#include<fstream>
#include<algorithm>
using namespace std;
#define MAXLEN 80000
//根据pivot分割数字
int partition(int a[], int l, int r, int k);
//选择第k小的数
int select(int a[], int l, int r, int k);
int main()
{
    int n = 0, k = 0;
    fstream se;
    se.open("select.in");
    se >> n >> k;
    //cout << n << k << endl;
    int* a = new int[MAXLEN];
    for (int i = 0; i < n; i++)
        se >> a[i];
    int tmp = select(a, 0, n - 1, k);
    delete[]a;

    ofstream outfile("select.out", ios::in | ios::out | ios::trunc);
    outfile << tmp;
    outfile.close();
    return 0;
}


int partition(int arr[], int l, int r, int x)
{
    //找到pivot放到数组末
    int i;
    for (i = l; i < r; i++)
        if (arr[i] == x)
            break;
    swap(arr[i], arr[r]);

    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] < x)
        {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

int select(int a[], int p, int r, int k)
{
    //小数量级情况下直接排序
    if (r-p< 75) 
    {
        sort(a + p, a + r + 1);
        return a[p + k - 1];
    }
    //组数为(r-p-4)/5
    for (int i = 0; i <= (r - p - 4) / 5; i++) 
    {
        //对每一组进行排序，再将中位数放在数组最前
        sort(a + p + 5 * i, a + p + 5 * i + 4);
        swap(a[p + i], a[p + 5 * i + 2]);

        int x = select(a, p, p + (r - p - 4) / 5, (r - p - 4) / 10);
        int l = partition(a, p, r, x), j = l - p + 1;
        //位于左半边
        if (k < j)
            return select(a, p, l, k);
        //位于右半边
        else if (k >= j)
            return select(a, l + 1, r, k - j);
        else
            return a[l];
    }
}
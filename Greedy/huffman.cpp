#include<iostream>
#include<algorithm>
#include<queue>
#include<fstream>
#include<iomanip>
using namespace std;
int main()
{
    fstream infile("huffman.in");
    ofstream outfile("huffman.out");
    priority_queue<double, vector<double>, greater<double>> q;
    int n;
    double tmp;
    infile >> n;
    for (int i = 0; i < n; i++)
    {
        infile >> tmp;
        q.push(tmp);
    }
    double sum = 0, min_num1 = 0, min_num2 = 0;
    while (q.size() != 1)//操作没有进行到根节点时
    {
        //取出最小的两个数
        min_num1 = q.top();
        q.pop();
        min_num2 = q.top();
        q.pop();
        sum += min_num1 + min_num2;
        q.push(min_num1 + min_num2);//入队列
    }
    outfile << fixed << setprecision(3) << sum;
    infile.close();
    outfile.close();
    return 0;
}
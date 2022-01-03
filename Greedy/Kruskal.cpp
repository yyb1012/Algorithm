#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<map>
#define inf 200000
using namespace std;
typedef struct edge{
	int n1;
	int n2;
	int w;
}edge;
int V, E;
int union_point(int x, int y, int* parent, int* rank);//合并两个节点
int find_root(int x, int* parent);//寻找根节点
int cmp(edge e1, edge e2);//排序规则

int main()
{
	int i = 0;
	int count = 0, sum = 0, flag = 0;
	fstream infile("kruskal.in");
	ofstream outfile("kruskal.out");
	infile >> V >> E;
	edge* e = new edge[E + 1];
	int* rank = new int[V + 1];
	int* parent = new int[V + 1];
	for (i = 1; i < V + 1; i++){
		parent[i] = -1;
		rank[i] = 0;
	}
	for (i = 1; i < E + 1; i++)
		infile >> e[i].n1 >> e[i].n2 >> e[i].w;
	sort(e + 1, e + E + 1, cmp);
	i = 1;
	
	while (count < V-1){
		flag = union_point(e[i].n1, e[i].n2, parent, rank);
		if (flag){
			sum += e[i].w;
			count++;
		}
		i++;
	}
	outfile << sum;
	delete[]parent;
	delete[]rank;
	delete[]e;
	infile.close();
	outfile.close();
	return 0;
}
//1代表合并成功，0代表失败
int union_point(int x, int y,int *parent,int *rank)//合并两个节点
{
	int x_root = find_root(x, parent);
	int y_root = find_root(y, parent);
	if (x_root == y_root)
		return 0;
	else{
		if (rank[x_root] > rank[y_root])
			parent[y_root] = x_root;
		else if (rank[x_root] < rank[y_root])
			parent[x_root] = y_root;
		else{
			parent[x_root] = y_root;
			rank[y_root]++;
		}
		return 1;
	}
}
int find_root(int x,int *parent)//寻找根节点
{
	int x_root = x;
	while (parent[x_root] != -1)
		x_root = parent[x_root];
	return x_root;
}
int cmp(edge e1, edge e2)//按照权值排序
{
	return e1.w < e2.w;
}

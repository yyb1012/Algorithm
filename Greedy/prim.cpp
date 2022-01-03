#include<iostream>
#include<algorithm>
#include<fstream>
#define inf 200000
using namespace std;
int V, E;
int prim(int** edge, int* closest, int* lowcost);
int main()
{
	int n1, n2, n3;
	int i = 0, j = 0;
	fstream infile("prim.in");
	ofstream outfile("prim.out");
	infile >> V >> E;
	int* lowcost = new int[V + 1];
	int* closest = new int[V + 1];
	int** edge = new int* [V + 1];
	for (i = 0; i < V + 1; i++)
		edge[i] = new int[V + 1];
	for (i = 0; i < V + 1; i++){
		for (j = 0; j < V + 1; j++){
				edge[i][j] = inf;
		}
	}
	for (i = 0; i < E ; i++){
		infile >> n1 >> n2 >> n3;
		if (edge[n1][n2] > n3){
			edge[n1][n2] = n3;
			edge[n2][n1] = n3;
		}
	}
	int tmp = prim(edge, closest, lowcost);
	//cout << tmp;
	outfile << tmp;
	for (int i = 0; i < V + 1; i++)
		delete[] edge[i];
	delete[] edge;
	delete[] closest;
	delete[] lowcost;
	infile.close();
	outfile.close();
	return 0;
}
int prim(int** edge, int* closest, int* lowcost)
{
	int min_, min_index, sum = 0;
	for (int i = 2; i < V + 1; i++)
	{//赋初值
		closest[i] = 1;
		lowcost[i] = edge[1][i];
	}
	closest[1] = 0;
	for (int i = 1; i < V; i++){
		min_ = inf;
		min_index = 0;
		for (int j = 2; j < V + 1; j++){
			//找到更小的，并保证不在S集合中
			if (lowcost[j] < min_ && lowcost[j] != 0){
				min_ = lowcost[j];//更新min值
				min_index = j;//记录当前最小权重的节点的编号
			}
		}
		sum += min_;
		lowcost[min_index] = 0;//加入S集
		for (int j = 2; j < V + 1; j++){
			if (lowcost[j] != 0 && edge[min_index][j] < lowcost[j]) {
				/*进入到该if语句里，说明刚选的节点k与当前节点j有更小的
				权重，则closest[j]的被连接节点需作修改为min_index*/
				lowcost[j] = edge[min_index][j];
				closest[j] = min_index;
			}
		}
	}
	//cout << sum << endl;
	return sum;
}
#include<iostream>
#include<algorithm>
#include<fstream>
#pragma warning(disable:4996)
#define inf 200001

using namespace std;
int V, E;
int Dijkstra(int** edge, int* dist, int* visited);
int main()
{
	int n1, n2, n3;
	fstream infile;
	ofstream outfile;
	infile.open("dijkstra.in");
	outfile.open("dijkstra.out");
	infile >> V >> E;
	int* dist = new int[V + 1];//申请数组
	int* visited = new int[V + 1];
	int** edge = new int*[V + 1];
	for (int i = 0; i < V + 1; i++)
		edge[i] = new int[V + 1];
	for (int i = 0;i < V; i++)
	{
		dist[i] = inf;
		visited[i] = 0;
	}
	for (int i = 0;i<V+1;i++)
	{
		for (int j = 1; j < V+1;j++)
			edge[i][j] = inf;
	}
	for (int i = 1; i < V + 1; i++)
		edge[i][i] = 0;
	for (int i = 1; i < E + 1; i++)
	{
		infile >> n1 >> n2 >> n3;
		if (edge[n1][n2] > n3)
		{
			edge[n1][n2] = n3;
			edge[n2][n1] = n3;
		}
	}
	int tmp=Dijkstra(edge, dist, visited);
	outfile << tmp;
	for (int i = 0; i < E + 1;i++)
		delete[] edge[i];
	delete[] edge;
	delete[] dist;
	delete[] visited;
	infile.close();
	outfile.close();
	return 0;
}

int Dijkstra(int **edge,int *dist,int *visited)
{
	for (int i = 1; i < V+1; i++)
	{
		dist[i] = edge[1][i];
	}
	visited[1] = 1;
	for (int i = 1; i < V; i++)
	{
		int minn = inf, temp = 0;
		for (int i = 1; i < V+1; i++){
			if (!visited[i] && dist[i] < minn){
				minn = dist[i];
				temp = i;
			}
		}
		visited[temp] = 1;
		for (int i = 1; i < V+1; i++){
			if (edge[temp][i] + dist[temp] < dist[i])
				dist[i] = edge[temp][i] + dist[temp];
		}
	}
	if (dist[V]==inf)
		return -1;
	else
		return dist[V];
}

#include<iostream>
#include<fstream>
#include<algorithm>
#include<set>
#define MAX 2510
using namespace std;
class point { public:int x, y; };
bool operator <(const point& p1, const point& p2);
void clr_jump(set<point>& p);//清除受控跳跃点
int w[2510] = { 0 };
int v[2510] = { 0 };
int dp[2510][2510] = { 0 };
int main()
{
	int V, N;
	fstream infile;
	ofstream outfile;
	infile.open("bag.in");
	outfile.open("bag.out");
	infile >> V >> N;
	for (int i = 1; i <= N; i++)
		infile >> w[i] >> v[i];

	set<point> p;//P集合
	p.insert({ 0,0 });
	for (int i = N; i > 0; i--)
	{
		set<point>q;//q集合
		for (set<point>::iterator it = p.begin(); it != p.end(); it++)
		{
			int qx = 0, qy = 0;
			qx = it->x + w[i], qy = it->y + v[i];
			if (qx <= V)//做初步筛选
				q.insert({ qx, qy });
		}
		//求p、q并集
		set_union(p.begin(), p.end(), q.begin(), q.end(), inserter(p, p.begin()));
		clr_jump(p);
	}
	outfile << p.rbegin()->y;
	return 0;
}

bool operator <(const point& p1, const point& p2)
{
	if (p1.x != p2.x)
		return p1.x < p2.x;
	else
		return p1.y < p2.y;
}

void clr_jump(set<point>& p)
{
	auto j = p.begin();
	int min = j->y;//记录下当前迭代器的y值
	j++;//从下一个元素开始比较
	for (; j != p.end();)
	{
		if (j->y < min)
			p.erase(j++);
		else
		{
			min = j->y;
			j++;
		}
	}
}

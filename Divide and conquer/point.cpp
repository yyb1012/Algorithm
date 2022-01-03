#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
//�� ��
class point
{
public:
	point() { this->x = 0, this->y = 0; }
	point(int m_x, int m_y) { this->x = m_x, this->y = m_y; }
	int x = 0, y = 0;
};
//�㼯�� ��
class p_set
{
public:
	int len = 0;
	vector<point> x_set;
	vector<point> y_set;
	void sortx();//sort by x
	void sorty();//sort by y
	double x_mid();//x�������λ��
	double select_min();//get smallest distance
};
vector<point> p;

/*�������*/
double distance(point& a, point& b);
/*ɨ��p1������x��ÿ������Y�����������dm֮�ڵ����е�(���6��)*/
double min_distance(p_set& p1, p_set& p2, double dm);
/*sort()�������*/
bool cmpx(point& a, point& b);
bool cmpy(point& a, point& b);
//a�о��봹ֱ�ָ���l�ľ�����dm֮�ڵĵ�ļ���,��ȥ���������dm�ĵ�
void remove_point(p_set& p, double dm);

int main()
{
	int n = 0;
	fstream p_file;
	p_file.open("point.in");
	p_file >> n;
	p_set pSet;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		p_file >> x >> y;
		point p_demo(x, y);
		p.push_back(p_demo);
	}
	pSet.sortx();
	pSet.sorty();

	double dm = pSet.select_min();
	ofstream outfile("point.out", ios::out | ios::trunc);
	outfile << setiosflags(ios::fixed) << setprecision(2) << dm;

	outfile.close();
	p_file.close();

	return 0;
}


double p_set::x_mid()
{
	int len = this->x_set.size();
	double mid = 0;
	if (len % 2 == 0)
	{
		//cout << this->x_set[len / 2].x << " " << this->x_set[len / 2 - 1].x << endl;
		mid = (double)(this->x_set[len / 2].x + this->x_set[len / 2 - 1].x) / 2;
	}
	else
		mid = (double)this->x_set[len / 2].x;

	return mid;
}

double distance(point& a, point& b)
{
	double length;
	length = (double)sqrt((a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y));
	return length;
}
bool cmpx(point& a, point& b)
{
	if (a.x < b.x)
		return true;
	return false;
}
bool cmpy(point& a, point& b)
{
	if (a.y < b.y)
		return true;
	return false;
}

void p_set::sortx()//sort by x
{
	x_set = p;
	sort(x_set.begin(), x_set.end(), cmpx);
}
void p_set::sorty()//sort by y
{
	y_set = p;
	sort(y_set.begin(), y_set.end(), cmpy);
}

void remove_point(p_set& p, double dm)
{
	/*���д��߾���>dm,remove*/
	double mid = (double)p.x_mid();
	//cout << mid << endl;
	unsigned int i = 0;
	for (i = 0; i < p.y_set.size(); i++)
	{
		if (fabs((double)p.y_set[i].x - mid) > dm)
			p.y_set.erase(p.y_set.begin() + i);
	}
}

double min_distance(p_set& p1, p_set& p2, double dm)
{
	double tmp = 1;
	unsigned int i = 0, j = 0;
	double x_right = 0, y_low = 0;
	//��Ϊ���ֻ�������㣬����Ϊ����ʱ��
	for (i = 0; i < p1.y_set.size(); i++)
	{
		int num = 0;
		x_right = (double)p1.y_set[i].x + dm;
		for (j = 0; j < p2.y_set.size() && p2.y_set[j].x <= x_right; j++)
		{
			double tmp = distance(p1.y_set[i], p2.y_set[j]);
			if (tmp < dm)
			{
				dm = tmp;
				num++;
			}
			if (num > 6)
				break;
		}
	}
	return dm;
}

double p_set::select_min()//get smallest distance
{
	unsigned int i = 0, j = 0, k = 0;
	if (this->x_set.size() == 1)
		return 0xffff;
	else if (this->x_set.size() == 2)
	{
		double tmp = distance(x_set[0], x_set[1]);
		//cout << tmp << endl;
		return tmp;
	}

	if (x_set.size() % 2 == 0)
		this->len = x_set.size() / 2;
	else
		this->len = x_set.size() / 2 + 1;

	p_set s1, s2;
	/*��ջ��x_setΪ����״̬*/
	for (i = 0; i < len; i++)
	{
		s1.y_set.push_back(this->x_set[i]);
		s1.x_set.push_back(this->x_set[i]);
	}
	for (j = 0; j < x_set.size() - len; j++, i++)
	{
		s2.y_set.push_back(this->x_set[i]);
		s2.x_set.push_back(this->x_set[i]);
	}

	//����yֵ����
	sort(s1.y_set.begin(), s1.y_set.end(), cmpy);
	sort(s2.y_set.begin(), s2.y_set.end(), cmpy);


	double d1 = s1.select_min();
	double d2 = s2.select_min();
	double dm = min(d1, d2);

	//�Ƴ��鲢ʱ���д��߾���>dm�ĵ�
	remove_point(s1, dm);
	remove_point(s2, dm);

	double dm1 = min_distance(s1, s2, dm);
	dm = min(dm, dm1);
	return dm;
}
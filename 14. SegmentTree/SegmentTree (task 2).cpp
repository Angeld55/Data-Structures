#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;
//We need to answer queries of this type : How many numbers between X-th and Y-th position are in the interval [L,K] (<=k and >= L)?
// the array is from distinct numbers !

#define HI(left,right,X, Y)  (left <= Y && right >= X) //hasIntersection
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))
struct node
{
	vector<int> m;
	bool created = false;
};

int getNextIndRight(int ind, int n)
{
	int diff = n - ind;
	if (diff % 2 == 0)
		return n - diff / 2;
	return n - diff / 2 - 1;

}
int getNextIndLeft(int ind, int n)
{
	int diff = n - ind;
	if (diff % 2 == 0)
		return ind + 1 + diff / 2;
	return (ind + diff / 2) + 1;
}
void BuildSegmentTree(int* a, node* t, int v, int tl, int tr, int left, int right)
{
	if (left == right)
		t[v].m.push_back(a[left - 1]);
	
	else
	{

		int tm = (tl + tr) / 2;
		BuildSegmentTree(a, t, v * 2, tl, tm, left, getNextIndRight(left, right));
		BuildSegmentTree(a, t, v * 2 + 1, tm + 1, tr, getNextIndLeft(left, right), right);
		std::merge(t[v * 2].m.begin(), t[v * 2].m.end(), t[v * 2 + 1].m.begin(), t[v * 2 + 1].m.end(), back_inserter(t[v].m));

	
	}
}

int countInInterval(vector<int>& m, int k, int l)
{

	auto it = lower_bound(m.begin(), m.end(), k);
	auto it2 = lower_bound(m.begin(), m.end(), l);

	bool firstOK = it != m.end();
	bool secondOK = it2 != m.end();

	if (!firstOK && !secondOK)
		return 0;
	else if (firstOK && !secondOK)
		return m.size() - distance(m.begin(), it);



	if (it == it2)
	{
		if (k <= (*it) && (*it) <= l)
			return 1;
		return 0;
	}

	int res = distance(it, it2);
	if (k <= (*it2) && (*it2) <= l)
		res++;
	return res;

}

int query(node* t, int* a, int left, int right, int n, int v, int X, int Y, int k, int l)
{
	if (!HI(left, right, X, Y))
		return 0;
	if (left >= X && right <= Y)
	{

		return countInInterval(t[v].m, k, l);
		return 0;
	}

	return  query(t, a, left, getNextIndRight(left, right), n, v * 2, X, Y, k, l) + query(t, a, getNextIndLeft(left, right), right, n, v * 2 + 1, X, Y, k, l);;

}

int main()
{


	int n, m;
	cin >> n >> m;

	int* a = new int[n];
	node* t = new node[4 * n + 1];


	for (int i = 0; i < n; i++)
	{
		cin >> a[i];

	}
	BuildSegmentTree(a, t, 1, 0, n - 1, 1, n);


	for (int i = 0; i < m; i++)
	{
		int x, y, k, l;
		cin >> x >> y >> k >> l;
		cout << query(t, a, 1, n, n, 1, x, y, k, l) << endl;
	}



}

#include <iostream>
using namespace std;

//we need to answer queries of this type: for a given value x and a range a[l…r] find the smallest i in the range l…r, such that a[i] is greater than x.


void update(long long* t, int v, int tl, int tr, int pos, int new_val) {
	if (tl == tr) {
		t[v] = new_val;
	}
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update(t, v * 2, tl, tm, pos, new_val);
		else
			update(t, v * 2 + 1, tm + 1, tr, pos, new_val);
		t[v] = t[v * 2] + t[v * 2 + 1];
	}
}

void buildSegmentTree(int* a, long long* t, int v, int tl, int tr)
{
	if (tl == tr)
	{
		t[v] = a[tl];
	}
	else
	{
		int tm = (tl + tr) / 2;
		buildSegmentTree(a, t, v * 2, tl, tm);
		buildSegmentTree(a, t, v * 2 + 1, tm + 1, tr);
		t[v] = t[v * 2] + t[v * 2 + 1];
	}
}
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
int query(long long* t, int* a, int left, int right, int n, int startInt, int x, int v)
{
	if (t[v] < x)
		return -1;
	if (right < startInt)
		return -1;
	if (left == right)
	{
		if (a[left - 1] >= x)
			return left;
		else
			return -1;
	}

	int res = query(t, a, left, getNextIndRight(left, right), n, startInt, x, v * 2);
	if (res != -1)
		return res;
	return query(t, a, getNextIndLeft(left, right), right, n, startInt, x, v * 2 + 1);

}
int main()
{


	int n, m;
	cin >> n >> m;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	long long* t = new long long[4 * n + 1];
	for (int i = 0; i < 4 * n + 1; i++)
		t[i] = -1;
		buildSegmentTree(a, t, 1, 0, n - 1);
	

	for (int i = 0; i < m; i++)
	{
		int queryType, arg1, arg2;
		cin >> queryType >> arg1 >> arg2;
		if (queryType == 1)
		{
			cout << query(t, a, 1, n, n, arg1 + 1, arg2, 1) << endl;
		}
		else
		{
			update(t, 1, 1, n, arg1 + 1, arg2);
			a[arg1] = arg2;
		}
	}
}

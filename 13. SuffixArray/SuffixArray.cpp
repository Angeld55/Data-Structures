#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;



namespace SA {

	const int MAXN = 1000010;

	int n;
	string s;

	int max(int a, int b)
	{
		return a >= b ? a : b;
	}

	int Left(int pos, int len)
	{

		return pos - len >= 0 ? pos - len : pos - len + n;
	}

	int Right(int pos, int len)
	{
		return pos + len < n ? pos + len : pos + len - n;
	}

	int sa[MAXN], id[MAXN];

	int key[MAXN], val[MAXN];
	int count[MAXN];
	void Sort(int* to) //stable !
	{
		int max_key = *max_element(key, key + n);
		fill(count, count + max_key + 1, 0);
		for (int i = 0; i < n; ++i)
			++count[key[i]];
		for (int i = 1; i <= max_key; ++i)
			count[i] += count[i - 1];
		for (int i = n - 1; i >= 0; --i)
			to[--count[key[i]]] = val[i];
	}

	void Group(int len) 
	{
		copy(id, id + n, val);
		id[sa[0]] = 0;
		for (int i = 1; i < n; ++i)
		{
			id[sa[i]] = id[sa[i - 1]];
			if (val[sa[i]] != val[sa[i - 1]] || val[Right(sa[i], len)] != val[Right(sa[i - 1], len)])
				id[sa[i]]++;
		}
	}

	vector<int> BuildSuffixArray(const string& in) 
	{
		s = in + '\0';
		n = (int)s.size();

		for (int i = 0; i < n; ++i)
			id[i] = s[i], key[i] = s[i], val[i] = i;
		Sort(sa);
		Group(0);

		for (int len = 1; id[sa[n - 1]] < n - 1; len *= 2){
			for (int i = 0; i < n; ++i)
				val[i] = Left(sa[i], len),
				key[i] = id[val[i]];
			Sort(sa);
			Group(len);
		}

		return vector<int>(sa, sa + n);
	}

	vector<int> BuildLCP(const string& in, const vector<int>& sa)
	{
		vector<int> lcp((int)(in).size());
		for (int i = 0; i < (int)(in.size()); ++i)
			key[sa[i]] = i;
		int len = 0;
		for (int i = 0; i < (int)in.size(); ++i){
			len = max(0, len - 1);
			int me = key[i], next = me + 1;
			if (next >= (int)(in.size())) len = 0;
			else {
				while (in[sa[me] + len] == in[sa[next] + len])
					++len;
				lcp[me] = len;
			}
		}
		return lcp;
	}

}

int main(){
	

	return 0;
}

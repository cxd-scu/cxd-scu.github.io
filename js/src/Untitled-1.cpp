#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int n)
{
	//判断一个数是否是素数
	for (int i = 2; i < n / 2; i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}
void trace(vector<int> curCircle, vector<int> left, vector<vector<int>> &results)
{
	if (left.size() == 1)
	{ //素数环最后一环
		if (isPrime(left[0] + curCircle[curCircle.size() - 1]) && isPrime(left[0] + 1))
		{
			//是否构成环
			curCircle.push_back(left[0]);
			results.push_back(curCircle);
		}
		return;
	}
	else
	{
		int endNum = curCircle[curCircle.size() - 1];
		for (int i = 0; i < left.size(); i++)
		{
			//判断剩余的数字与当前环中最后一个数字之和是否为素数
			if (isPrime(left[i] + endNum))
			{
				int curNum = left[i];
				left.erase(left.begin() + i);
				curCircle.push_back(curNum);
				trace(curCircle, left, results);
				curCircle.pop_back();
				left.insert(left.begin() + i, curNum);
			}
		}
	}
}
vector<vector<int>> primeCircle(int n)
{
	vector<int> curCircle; //当前环
	vector<int> left;	   //未使用的数字

	//初始化
	curCircle.push_back(1);
	for (int i = 1; i < n; i++)
	{
		left.push_back(i + 1);
	}
	vector<vector<int>> results; //结果
	trace(curCircle, left, results);
	return results;
}

int main()
{
	int n = 0;
	cin >> n;
	vector<vector<int>> results = primeCircle(n);
	for (int i = 0; i < results.size(); i++)
	{
		for (int j = 0; j < results[i].size(); j++)
			cout << results[i][j] << " ";
		cout << endl;
	}
}
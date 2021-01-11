#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node
{ //数据节点类
public:
	int weight;		   //重量
	int value;		   //价值
	int upperBound;	   //上界
	int level;		   //当前判断层次
	vector<int> trace; //路径

	Node(int weight, int value, int upperBound, int level, vector<int> trace)
	{
		this->weight = weight;
		this->value = value;
		this->upperBound = upperBound;
		this->level = level;
		this->trace = trace;
	}
};
class Problem
{ //问题类
public:
	int *weights; //权重数组
	int *values;  //价值数组
	int CAPACITY; //容量
	int LEVEL;	  //物品数量
	vector<Node> result;
	void input()
	{ //处理输入
		cin >> LEVEL;
		weights = new int[LEVEL];
		values = new int[LEVEL];
		for (unsigned int i = 0; i < LEVEL; i++)
			cin >> weights[i];
		for (unsigned int i = 0; i < LEVEL; i++)
			cin >> values[i];
		cin >> CAPACITY;
		vector<int> trace;

		Node root(0, 0, CAPACITY, 0, trace);
		generateNode(root);
	}
	void output()
	{ //按要求输出
		Node cur = result[0];
		for (unsigned int i = 1; i < result.size(); i++)
			if (cur.value < result[i].value)
				cur = result[i];
		for (unsigned int i = 0; i < cur.trace.size(); i++)
			cout << cur.trace[i] << " ";
		cout << endl
			 << cur.value << endl;
	}
	void generateNode(Node node)
	{
		vector<int> nodeTrace = node.trace;
		nodeTrace.push_back(0);
		vector<int> leftTrace = nodeTrace;
		nodeTrace.pop_back();
		nodeTrace.push_back(1);
		vector<int> rightTrace = nodeTrace;

		int curLevel = node.level;
		if (curLevel == LEVEL) //判断叶节点
			result.push_back(node);
		else
		{
			Node left(node.weight, node.value, node.upperBound, node.level + 1, leftTrace);
			Node right(node.weight + weights[curLevel], node.value + values[curLevel], node.upperBound - weights[curLevel], node.level + 1, rightTrace);
			generateNode(left);		   //生成节点
			if (right.upperBound >= 0) //剪枝
				generateNode(right);
		}
	}
};
int main()
{
	Problem p;
	p.input();
	p.output();
}
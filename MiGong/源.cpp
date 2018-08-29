#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct  node
{
	int x, y;
};

struct mg {
	node start;
	vector<char> key;
	
};

int res = 0x7FFFFFFF;
void DFS(mg &f, vector<vector<char>> &a, vector<vector<bool>> &visited, int i, int j, int n, int m, int count, vector<node> path);
void findPath(mg &f, vector<vector<char>> &a, vector<vector<bool>> &visited, int i, int j, int n, int m, int count, vector<node> path) {
	DFS(f, a, visited, i + 1, j, n, m,count,path);//����
	DFS(f, a, visited, i, j + 1, n, m, count, path);//����
	DFS(f, a, visited, i - 1, j, n, m, count, path);//����
	DFS(f, a, visited, i, j - 1, n, m, count, path);//����
}


void DFS(mg &f, vector<vector<char>> &a, vector<vector<bool>> &visited, int i, int j, int n, int m, int count, vector<node> path) {
	if (i == n || i < 0 || j == m || j < 0)
		return;
	if (!visited[i][j]) {
		visited[i][j] = true;
		if (a[i][j] == '1' || a[i][j] == '2') {//��ͨ�е�·
			node temp;
			temp.x = i;
			temp.y = j;
			path.push_back(temp);
			findPath(f,a, visited, i, j, n, m, count + 1, path);
		}
		else if (a[i][j] >= 'a' && a[i][j] <= 'z') {//��Կ��
			node temp;
			temp.x = i;
			temp.y = j;
			path.push_back(temp);
			f.key.push_back(a[i][j]);
			findPath(f, a, visited, i, j, n, m, count + 1, path);
			f.key.pop_back();
		}
		else if (a[i][j] >= 'A' && a[i][j] <= 'Z') {//�����ţ��鿴�Ƿ���Կ��
			bool flag = false;
			for (int k = 0; k < f.key.size(); ++k) {
				if (a[i][j] - f.key[k] == 'A' - 'a') {
					flag = true;
					break;
				}
			}
			if (!flag)//û��Կ��,��·��ͨ
			{
				visited[i][j] = false;
				return;
			}
			node temp;
			temp.x = i;
			temp.y = j;
			path.push_back(temp);
			findPath(f, a, visited, i, j, n, m, count + 1, path);
		}
		else if (a[i][j] == '3') {//�ҵ��յ������Сֵ
			res = min(res, count);
			visited[i][j] =false;
			return;
		}
		visited[i][j] = false;
	}
	
}

void solution() {
	int n, m;
	cin >> n >> m;
	vector<vector<char>> a(n, vector<char>(m));
	vector<vector<bool>> visited(n, vector<bool>(m,false));
	mg flag;
	vector<node> path;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> a[i][j];
			if (a[i][j] == '2') {
				flag.start.x = i;
				flag.start.y = j;
			}
			
		}
			
	}
	DFS(flag, a, visited, flag.start.x, flag.start.y, n,m,0, path);
	if (res == 0x7FFFFFFF)
		res = 0;	
	cout << res;
}

int  main() {
	solution();
	return 0;
}
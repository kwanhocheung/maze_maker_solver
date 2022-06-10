#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
//DFS

int endY, endX, minStep = 1000;		
int v[100][100];					
int dx[4] = { 0, 1, 0, -1 }; 
int dy[4] = { 1, 0, -1, 0 };


typedef struct node
{
	int x;
	int y;
}node;
node stack[100];
node s_min[100];
int top = 0;
int sNum = 1;
int row = 7;
int col = 7;


void core(vector<vector<int>> map, int x, int y, int step)
{
	
	if (y == endY && x == endX)
	{
		sNum++;
		
		if (step < minStep)
		{
			minStep = step;

			memset(s_min, 0, sizeof(s_min));
			for (int i = 0; i < step; i++)
				s_min[i] = stack[i];
		}
		return;
	}

	
	for (int k = 0; k < 4; k++)
	{
		int nextX = x + dx[k];
		int nextY = y + dy[k];

		if (nextX < 0 || nextX > row || nextY < 0 || nextY > col)
			continue;

		if ((map[nextX][nextY] == 0 || map[nextX][nextY] == 2) && v[nextX][nextY] == 0) 
		{
			v[nextX][nextY] = 1;

			stack[top].x = nextX;
			stack[top].y = nextY;
			top++;

			core(map, nextX, nextY, step + 1);

			v[nextX][nextY] = 0;
			top--;
		}
	}

	return;
}

vector<vector<int>> DFS(vector<vector<int>> map, int startY, int startX)
{
	
	v[startX][startY] = 1;

	
	//endX = 1;
	//endY = 4;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == 2)
			{
				endX = i;
				endY = j;
				break;
			}
		}
	}
	//cout << " endx = " << endX << ", endy = " << endY << endl;

	
	row = map.size() - 1;
	col = map[0].size() - 1;
	core(map, startX, startY, 0);

	stack[0].x = startX;
	stack[0].y = startY;

	/*for (int i = 0; i < minStep; i++)
		cout << s_min[i].x << " " << s_min[i].y << endl;*/

		
	vector<vector<int>> path;
	vector<int> start;
	start.push_back(startX);
	start.push_back(startY);
	path.push_back(start);

	
	if (minStep == 1000) return path;

	for (int i = 0; i < minStep; i++)
	{
		vector<int> a;
		a.push_back(s_min[i].x);
		a.push_back(s_min[i].y);
		path.push_back(a);
	}

	return path;
}

int main()
{
	vector<vector<int>> map = {
	{0,0,1,0,0,0,1,0,1,0,0,1,0,0,0},
	{1,0,0,0,1,1,0,0,0,1,0,1,0,1,1},
	{1,1,0,1,0,0,1,0,1,0,0,1,0,1,0},
	{1,0,0,0,1,0,0,0,0,1,0,1,0,0,0},
	{0,1,0,1,0,1,0,1,1,1,0,1,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,0,1,0,1,0,1,0,1,1},
	{0,1,0,0,0,0,0,0,1,0,1,0,1,0,1},
	{0,0,0,1,0,1,0,1,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,0,0,0,1,1,0,1,1,0},
	{1,0,0,0,0,1,0,1,0,0,0,1,1,1,0},
	{2,0,1,0,1,0,0,0,1,0,1,0,1,0,0},
	{1,0,1,0,1,0,1,0,1,0,0,0,1,0,1},
	{0,0,1,0,1,0,1,0,1,0,1,0,0,1,0},
	{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0}
	};

	int startX = 0, startY = 0;

	cout << "startX: ";
	cin >> startX;
	cout << "startY: ";
	cin >> startY;


	vector<vector<int>> path = DFS(map, startY, startX);

	cout << "{";
	for (int i = 0; i < path.size(); ++i)
		cout << "{" << path[i][0] << ", " << path[i][1] << "}" << (i == path.size() - 1 ? "" : ",");
	cout << "}\n";

	return 0;
}
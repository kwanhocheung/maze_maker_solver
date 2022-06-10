#include <iostream>
#include<vector>
#include<stack>
#include<time.h>
#include <stdlib.h>

using namespace std;
void digwall(vector<vector<int>>& maze);
void dfs(vector<vector<int>>& maze, int i, int j, stack<pair<int, int>>& record);
void print_maze(vector<vector<int>> maze);

int main()
{
    int row, col;
    cout << "row: ";
    cin >> row;
    cout << "col: ";
    cin >> col;


    vector<int>sub(col, 1);
    vector<vector<int>>maze(row, sub);

    digwall(maze);

    //make 3=0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (maze[i][j] == 3)
            {
                maze[i][j] = 0;
            }
        }
    }

    vector<pair<int, int>>Pair;
    pair<int, int>subpair;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (maze[i][j] == 0)
            {
                subpair = make_pair(i, j);
                Pair.push_back(subpair);

            }
        }
    }
    

    //random make 1 cell, assign to goal.
    int pick_goal = rand() % Pair.size();
    maze[Pair[pick_goal].first][Pair[pick_goal].second] = 2;
    
    //print
    print_maze(maze);
    return 0;//end
}
void digwall(vector<vector<int>>&maze)
{
    stack<pair<int, int>>record;
    maze[0][0] = 0;
    dfs(maze, 0, 0, record);

    cout << "stack: " << endl;
    for (int i = 0; i < record.size(); i++)
    {
        cout << record.top().first << " " << record.top().second << endl;
        record.pop();
    }
    cout << endl;
}

void dfs(vector<vector<int>>& maze, int i, int j, stack<pair<int, int>>&record)
{
    int n = maze.size();
    int m = maze[0].size();
    int count = 0; 

    //cout << "curr index: " << i << " " << j << endl;
    if ( i < 0 || i >= n || j < 0 || j >= m|| maze[i][j] != 0)
    {
        return;
    }
    vector<pair<int, int>>direction;
    
    //random pick 1 neighbor
    //if the neighbor exist and never visited
    //add in direction vector
    //chack in range-down
    if (i + 1 < n)
    {
        //check if the neighbor are wall?
        if (maze[i + 1][j] == 1)
        {
            pair<int, int>down;
            down = make_pair(i + 1, j);
            direction.push_back(down);
            count++;
            cout << "neighbor: "<<down.first << " " << down.second << endl;
        }
    }
    //check in rnage-up
    if (i - 1 > 0)
    {
        //check if the neighbor are wall?
        if (maze[i - 1][j] == 1)
        {
            pair<int, int>up;
            up = make_pair(i - 1, j);
            direction.push_back(up);
            count++;
            cout << "neighbor: " << up.first << " " << up.second << endl;
        }
    }
    //check in range-right
    if (j + 1 < m)
    {
        //check if the neighbor are wall?
        if (maze[i][j + 1] == 1)
        {
            pair<int, int>right;
            right = make_pair(i, j + 1);
            direction.push_back(right);
            count++;
            cout << "neighbor: " << right.first << " " << right.second << endl;
        }
    }
    
    //check in range-left
    if (j - 1 > 0)
    {
        //check if the neighbor are wall?
        if (maze[i][j - 1] == 1)
        {
            pair<int, int>left;
            left = make_pair(i, j - 1);
            direction.push_back(left);
            count++;
            cout << "neighbor: " << left.first << " " << left.second << endl;
        }
    }
    //no neighbor
    if (count == 0)
    {
        return;
    }
    
       //rnadom pick 1 neighbor
       int random = rand() % count;
       cout << "random pick: "<< direction[random].first << " " << direction[random].second << endl;
       maze[direction[random].first][direction[random].second] = 0;
       pair<int, int> p;
       p = make_pair(direction[random].first, direction[random].second);
       record.push(p);
    

    //mark current maze already visited
    maze[i][j] = 3;

    //clear the direction
    direction.clear();
    
    //recursion
    dfs(maze, i - 1, j, record);
    dfs(maze, i + 1, j, record);
    dfs(maze, i, j - 1, record);
    dfs(maze, i, j + 1, record);
}

void print_maze(vector<vector<int>> maze)
{
    int n = maze.size();
    int m = maze[0].size();
    cout << "{";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (j == 0)
            {
                cout << "{" << maze[i][j] << ",";
            }
            if (j == m - 1)
            {
                cout << maze[i][j] << "}";
            }
            else
            {
                cout << maze[i][j] << ",";
            }
        }
        if (i == n - 1)
        {
            cout << "}" << endl;
        }
        else
        {
            cout << "," << endl;
        }
    }
}


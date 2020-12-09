//HW1 A1045518 DFS
#include<iostream>
#include<fstream>
#include<stack>
#define Maze "smallMaze"
#define FILE Maze".txt"
using namespace std;
struct pos //point format
{
    int x;
    int y;
    int dir; //record the direction before push into the stack
};
int run(string *Map,pos *mov,stack<pos> &way,int **ifrun)
{
    pos now; //point now
    pos next; //new point
    int nodes=0; //expand nodes
    while(!way.empty())
    {
        now=way.top();
        way.pop();
        for(int i=now.dir;i<4;i++)
        {
            if(i==0) //first time expand the point
            {
                nodes++;
            }
            next.x=now.x+mov[i].x;
            next.y=now.y+mov[i].y;
            if(Map[next.x][next.y]=='G') //if next point is goal
            {
                way.push(now);
                return nodes;
            }
            else if(Map[next.x][next.y]==' ' && ifrun[next.x][next.y]!=1) //if next point can walk (not a wall) and haven't been gone
            {
                now.dir=i+1;
                next.dir=0;
                ifrun[next.x][next.y]=1;
                way.push(now);
                way.push(next);
                break;
            }
        }
    }
    return -1;  //no road in the maze
}
int main(void)
{
    ifstream fin; //file open
    fin.open(FILE);
    if(!fin) //file cannot open
    {
        cout<<"File open failed!"<<endl;
        return 0;
    }
    string str;
    int row=0;
    while(getline(fin,str)) //check rows of data
    {
        row++;
    }
    fin.close();
    pos mov[4]={{-1,0},{0,1},{1,0},{0,-1}};
    stack<pos> way; //stack
    pos start; //start point
    bool stfind=false; //check if find start point
    string *Map=new string[row]; //create map
    int **ifrun=new int*[row]; //to record run point
    fin.open(FILE);
    for(int i=0;i<row;i++)
    {
        getline(fin,Map[i]); //load data from file
        ifrun[i]=new int[Map[i].size()];
        for(int j=0;j<Map[i].size();j++)
        {
            ifrun[i][j]=0; //initialize the run point
            if(!stfind)
            {
                if(Map[i][j]=='S') //find start point
                {
                    start.x=i;
                    start.y=j;
                    start.dir=0;
                    stfind=true;
                    way.push(start);
                    ifrun[i][j]=1;
                }
            }
        }
    }
    fin.close();
    int k=run(Map,mov,way,ifrun);
    if(k!=-1) //if there has a road
    {
        int step=0;
        pos dot;
        while(!way.empty())
        {
            dot=way.top();
            way.pop();
            Map[dot.x][dot.y]='.';
            step++;
        }
        Map[dot.x][dot.y]='S';
        cout<<"Type : DFS"<<endl;
        cout<<"Maze : "<<Maze<<endl;
        cout<<"Total steps : "<<step<<endl;
        cout<<"Expanded nodes : "<<k<<endl;
        for(int i=0;i<row;i++)
        {
            cout<<Map[i]<<endl;
        }
    }
    else
    {
        cout<<"No road!"<<endl;
    }
    return 0;
}

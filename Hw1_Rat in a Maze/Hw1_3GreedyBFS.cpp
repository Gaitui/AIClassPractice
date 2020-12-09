//H
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<map>
#include<iterator>
#define Maze "smallMaze"
#define FILE Maze".txt"
using namespace std;
struct pos //point format
{
    int x;
    int y;
    int dis; //distance to goal
};
struct mapoper //map operator
{
    bool operator()(pos a,pos b)
    {
        return((a.x<b.x) || ((a.x==b.x) && (a.y<b.y)));
    }
};
struct pqoper //priority queue operator
{
    bool operator()(pos a,pos b)
    {
        return (a.dis>b.dis);
    }
};
int nodes=0; //expand nodes
pos run(string *Map,pos *mov,pos start,pos goal,map<pos,pos,mapoper> &way,int **ifrun)
{
    priority_queue<pos,vector<pos>,pqoper> leaf; //priority queue
    start.dis=abs(start.x-goal.x)+abs(start.y-goal.y);
    leaf.push(start);
    pos now;  //point now
    pos next; //new point
    map<pos,pos,mapoper>::iterator iter;
    while(!leaf.empty())
    {
        now=leaf.top();
        leaf.pop();
        if(ifrun[now.x][now.y]) //if the point has gone before
        {
            ifrun[now.x][now.y]--; //record the point has already gone
            nodes++;
        }
        else
        {
            continue;
        }
        for(int i=0;i<4;i++)
        {
            next.x=now.x+mov[i].x;
            next.y=now.y+mov[i].y;
            next.dis=abs(next.x-goal.x)+abs(next.y-goal.y);
            if(Map[next.x][next.y]=='G') //if next point is goal
            {
                way[next]=now;
                return next;
            }
            else if(Map[next.x][next.y]==' ') //if next point can walk (not a wall)
            {
                iter=way.find(next);
                if(iter!=way.end()) //check if the point has gone before
                {
                    if(iter->first.dis>next.dis) //if new point step count is lower than the step count save in map
                    {
                        way[next]=now; //change nows point to be the point it come form
                    }
                }
                else
                {
                    way[next]=now; //record the new point where it come from
                }
                leaf.push(next); //push into priority queue
            }
        }
    }
    pos fail; //no road in the maze
    fail.x=-1;
    return fail;
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
    map<pos,pos,mapoper> way; //record point come from
    pos start; //start point
    pos goal; //goal point
    bool stfind=false; //check if find start point
    bool gofind=false; //check if find goal point
    string *Map=new string[row]; //create map
    int **ifrun=new int*[row]; //to record run point
    fin.open(FILE);
    for(int i=0;i<row;i++)
    {
        getline(fin,Map[i]); //load data from file
        ifrun[i]=new int[Map[i].size()];
        for(int j=0;j<Map[i].size();j++)
        {
            ifrun[i][j]=1; //initialize the run point
            if(!stfind || !gofind)
            {
                if(Map[i][j]=='S') //find start point
                {
                    start.x=i;
                    start.y=j;
                    stfind=true;
                }
                else if(Map[i][j]=='G') //find goal point
                {
                    goal.x=i;
                    goal.y=j;
                    gofind=true;
                }
            }
        }
    }
    fin.close();
    pos k=run(Map,mov,start,goal,way,ifrun);
    if(k.x!=-1) //if there has a road
    {
        int step=1;
        map<pos,pos,mapoper>::iterator iter;
        iter=way.find(k);
        k=iter->second;
        while(Map[k.x][k.y]!='S')
        {
            Map[k.x][k.y]='.';
            iter=way.find(k);
            k=iter->second;
            step++;
        }
        cout<<"Type : Greedy"<<endl;
        cout<<"Maze : "<<Maze<<endl;
        cout<<"Total steps : "<<step<<endl;
        cout<<"Expanded nodes : "<<nodes<<endl;
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

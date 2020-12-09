//HW1 A1045518 BFS
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
};
struct mapoper //map operator
{
    bool operator()(pos a,pos b)
    {
        return((a.x<b.x) || ((a.x==b.x) && (a.y<b.y)));
    }
};
int nodes=0; //expand nodes
pos run(string *Map,pos *mov,pos start,map<pos,pos,mapoper> &way)
{
    queue<pos> leaf; //queue
    leaf.push(start);
    pos now; //point now
    pos next; //new point
    map<pos,pos,mapoper>::iterator iter;
    while(!leaf.empty())
    {
        now=leaf.front();
        leaf.pop();
        nodes++;
        for(int i=0;i<4;i++)
        {
            next.x=now.x+mov[i].x;
            next.y=now.y+mov[i].y;
            if(Map[next.x][next.y]=='G') //if next point is goal
            {
                way[next]=now;
                return next;
            }
            else if(Map[next.x][next.y]==' ') //if next point can walk (not a wall)
            {
                iter=way.find(next);
                if(iter==way.end()) //check if the point has gone before
                {
                    way[next]=now; //record the new point where it come from
                    leaf.push(next); //push into queue
                }
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
    bool stfind=false; //check if find start point
    string *Map=new string[row]; //create map
    fin.open(FILE);
    for(int i=0;i<row;i++)
    {
        getline(fin,Map[i]); //load data from file
        for(int j=0;j<Map[i].size();j++)
        {
            if(!stfind)
            {
                if(Map[i][j]=='S') //find start point
                {
                    start.x=i;
                    start.y=j;
                    stfind=true;
                }
            }
        }
    }
    fin.close();
    pos k=run(Map,mov,start,way);
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
        cout<<"Type : BFS"<<endl;
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

#include<iostream>
#include<fstream>
#include<stack>
#include<queue>
#include<string>
#include<sstream>
using namespace std;

int row, col, battery;
int BatteryRow, BatteryCol;
int BatteryNum;
int step=0;
char input;
int transMatrix[2000][2000];
int adj[20000][20000];
int d[2000];
bool visit[2000]= {false};
bool Clean[2000]= {false};
int parent[2000];
string Location[1000000];
int numOfVertex=0;
stack<int> trail;
int RobotRow,RobotCol,RobotBattery;
ifstream fin;
ofstream fout;

void initClean()
{
    for(int i=1;i<=numOfVertex;i++)
    {
        Clean[i] = false;
    }
    return;
}

void initDistance()
{
    for(int i=0; i<2000; i++)
    {
        d[i]=1000000;
    }
    for(int i=1; i<=numOfVertex; i++)
    {
        if(i==BatteryNum);
        else
        {
            if(adj[BatteryNum][i]!=1000000)
            {
                d[i] = 1;
            }
        }
    }
    return;
}

void Dijkstra(int source)
{
    for(int i=1; i<=numOfVertex; i++)
    {
        visit[i]=false;
    }
    initDistance();
    d[source]=0;
    visit[source] =true;
    parent[source] = source;
    cout<<source<<endl;

    for(int k=1; k<=numOfVertex; k++)
    {
        int a=-1, b=-1, Min = 1000000;
        for(int i=1; i<=numOfVertex; i++)
        {
            if(!visit[i] && d[i] < Min)
            {
                a = i;
                Min = d[i];

            }
        }
        if(a == -1)
            break;

        visit[a] = true;

        for(int b=1; b<=numOfVertex; b++)
        {
            if(!visit[b] && ((d[a] + adj[a][b]) < d[b]))
            {
                d[b] = d[a] + adj[a][b];
                parent[b] = a;
            }
        }
    }
}

void find_path(int x)   // パ癬翴x翴程祏隔畖
{
    if(x!=0)
    {
        if (x != parent[x]) // рぇ玡隔畖常ㄓ
        find_path(parent[x]);
        step++;
        trail.push(x);
        Clean[x]=true;
    }
}

void O_find_path(int x)   // パ癬翴x翴程祏隔畖
{
    if(x!=0)
    {
        if (x != parent[x]) // рぇ玡隔畖常ㄓ
        O_find_path(parent[x]);
        step++;
        trail.push(x);
        Clean[x]=true;
        fout << Location[x] << endl;  // р瞷竚ㄓ
    }
}

void goBack()
{
    trail.pop();
    while(!trail.empty())
    {
        //cout<<Location[trail.top()]<<endl;
        trail.pop();
        step++;
    }
    RobotBattery = battery;
    step++;
    return;
}

void O_goBack()
{
    trail.pop();
    while(!trail.empty())
    {
        fout<<Location[trail.top()]<<endl;
        trail.pop();
        step++;
    }
    fout<<Location[BatteryNum]<<endl;
    RobotBattery = battery;
    step++;
    return;
}

void initAdj()
{
    for(int i=0; i<=numOfVertex; i++)
    {
        for(int j=0; j<=numOfVertex; j++)
        {
            adj[i][j] = 1000000;
            //cout<<i<<" "<<j<<endl;
        }
    }
    return ;
}

void BuildAdj()
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            if(transMatrix[i][j]!=0)
            {
                if(i==0||j==0||i==row-1||j==col-1)
                {
                    if(i==0&&j==0) //オ
                    {
                        if(transMatrix[i][j+1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1000000;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1000000;
                        }
                    }
                    else if(i==0&&j==col-1) //
                    {
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j-1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j-1]]=1000000;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1000000;
                        }
                    }
                    else if(i==row-1&&col==0) //オ
                    {
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1000000;
                        }
                        if(transMatrix[i][j+1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1000000;
                        }
                    }
                    else if(i==row-1&&j==col-1) //
                    {
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1000000;
                        }
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j-1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j-1]]=1000000;
                        }
                    }
                    else if(i==0)
                    {
                        if(transMatrix[i][j+1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1000000;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1000000;
                        }
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j-1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j-1]]=1000000;
                        }
                    }
                    else if(i==row-1)
                    {
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j-1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j-1]]=1000000;
                        }
                        if(transMatrix[i][j+1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1000000;
                        }
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1000000;
                        }
                    }
                    else if(j==0)
                    {
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1000000;
                        }
                        if(transMatrix[i][j+1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1000000;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1000000;
                        }
                    }
                    else if(j==col-1)
                    {
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i-1][j]]=1000000;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i+1][j]]=1000000;
                        }
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1;
                        }
                        else
                        {
                            adj[transMatrix[i][j]][transMatrix[i][j+1]]=1000000;
                        }
                    }
                }
                else
                {
                    if(transMatrix[i][j+1]!=0)
                    {
                        adj[transMatrix[i][j]][transMatrix[i][j+1]]=1;
                    }
                    else
                    {
                        adj[transMatrix[i][j]][transMatrix[i][j+1]]=1000000;
                    }
                    if(transMatrix[i][j-1]!=0)
                    {
                        adj[transMatrix[i][j]][transMatrix[i][j-1]]=1;
                    }
                    else
                    {
                        adj[transMatrix[i][j]][transMatrix[i][j-1]]=1000000;
                    }
                    if(transMatrix[i+1][j]!=0)
                    {
                        adj[transMatrix[i][j]][transMatrix[i+1][j]]=1;
                    }
                    else
                    {
                        adj[transMatrix[i][j]][transMatrix[i+1][j]]=1000000;
                    }
                    if(transMatrix[i-1][j]!=0)
                    {
                        adj[transMatrix[i][j]][transMatrix[i-1][j]]=1;
                    }
                    else
                    {
                        adj[transMatrix[i][j]][transMatrix[i-1][j]]=1000000;
                    }
                }
            }
        }
    }
}


int main(int argc, char *argv[])
{
    stringstream s;
    string location;
    stringstream inlocation;
    stringstream outlocation;
    //inlocation<<"./"<<argv[1]<<"/floor.data";
    //outlocation<<"./"<<argv[1]<<"/final.path";
    //fin.open(inlocation.str());
    //fout.open(outlocation.str());
    fin.open("floor.data");
    fout.open("final.path",ios::out);
    fin>>row>>col>>battery;
    cout<<"start reading floor.data"<<endl;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            fin>>input;
            if(input=='R')
            {
                transMatrix[i][j]=++numOfVertex;
                BatteryNum = numOfVertex;
                BatteryRow = i;
                BatteryCol = j;
                s.str("");
                s.clear();
                s<<i<<" "<<j;
                location = s.str();
                Location[numOfVertex]=location;
            }
            else if(input=='1')
            {
                transMatrix[i][j]=0 ;
            }
            else if(input=='0')
            {
                transMatrix[i][j]=++numOfVertex;
                s.str("");
                s.clear();
                s<<i<<" "<<j;
                location = s.str();
                Location[numOfVertex]=location;
            }
            else
            {
                j--;
            }
        }
    }
    cout<<"finished reading floor.data"<<endl;

    RobotRow = BatteryRow;
    RobotCol = BatteryCol;
    RobotBattery = battery;
    fin.close();
    //matrix finish
    /*cout<<"Begin initializing Adj"<<endl;
    initAdj();
    cout<<"End initializing Adj"<<endl;*/
    cout<<"Begin building Adj"<<endl;
    BuildAdj();
    cout<<"End building Adj"<<endl;
    cout<<"Begin Dijkstra"<<endl;
    Dijkstra(BatteryNum);
    cout<<"finished Dijkstra"<<endl;
    Clean[BatteryNum]=true;
    for(int i=1;i<=numOfVertex;i++)
    {
        if(!Clean[i])
        {
            find_path(i);
            goBack();
        }
    }
    fout<<step<<endl;
    initClean();
    Clean[BatteryNum]=true;
    for(int i=1;i<=numOfVertex;i++)
    {
        if(!Clean[i])
        {
            O_find_path(i);
            O_goBack();
        }
    }
    fout.close();
    //cout<<BatteryRow<<","<<BatteryCol<<endl;
    cout<<BatteryNum<<endl;
    return 0;
}

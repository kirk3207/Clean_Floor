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
char matrix[1000][1000];
int transMatrix[1000][1000];
int adj[1000][1000]= {0};
int d[1000];
bool visit[1000]= {false};
bool Clean[1000]= {false};
int parent[1000];
string Location[1000];
int numOfVertex=0;
stack<int> trail;
int RobotRow,RobotCol,RobotBattery;

void initDistance()
{
    for(int i=0; i<1000; i++)
    {
        d[i]=10000;
    }
    for(int i=1; i<=numOfVertex; i++)
    {
        if(i==BatteryNum);
        else
        {
            if(adj[i][BatteryNum])
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

    for(int k=1; k<=numOfVertex; k++)
    {
        int a=-1, b=-1, Min = 10000;
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

void find_path(int x)   // 印出由起點到x點的最短路徑
{
    if (x != parent[x]) // 先把之前的路徑都印出來
        find_path(parent[x]);
    step++;
    trail.push(x);
    Clean[x]=true;
    cout << Location[x] << endl;  // 再把現在的位置印出來
}

void goBack()
{
    trail.pop();
    while(!trail.empty())
    {
        cout<<Location[trail.top()]<<endl;
        trail.pop();
        step++;
    }
    cout<<RobotRow<<" "<<RobotCol;
    RobotBattery = battery;
    step++;
    return;
}

void initAdj()
{
    for(int i=0; i<numOfVertex; i++)
    {
        for(int j=0; j<numOfVertex; j++)
        {
            adj[i][j] = 10000;
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
                if(transMatrix[i][j+1]!=0)
                {
                    adj[transMatrix[i][j]][transMatrix[i][j+1]]=1;
                }
                if(transMatrix[i][j-1]!=0)
                {
                    adj[transMatrix[i][j]][transMatrix[i][j-1]]=1;
                }
                if(transMatrix[i+1][j]!=0)
                {
                    adj[transMatrix[i][j]][transMatrix[i+1][j]]=1;
                }
                if(transMatrix[i-1][j]!=0)
                {
                    adj[transMatrix[i][j]][transMatrix[i-1][j]]=1;
                }
            }
        }
    }
    /*for(int i=1;i<=numOfVertex;i++)
    {
            for(int j=1;j<numOfVertex;j++)
            {
                    if(i==j)
                    {
                            adj[i][j]=0;
                    }
            }
    }*/
}


int main()
{
    ifstream fin;
    ofstream fout;
    stringstream s;
    string location;
    fin.open("floor.data");
    fout.open("final.path",ios::out);
    fin>>row>>col>>battery;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            fin>>matrix[i][j];
            if(matrix[i][j]=='R')
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
            else if(matrix[i][j]=='1')
            {
                transMatrix[i][j]=0 ;
            }
            else if(matrix[i][j]=='0')
            {
                transMatrix[i][j]=++numOfVertex;
                s.str("");
                s.clear();
                s<<i<<" "<<j;
                location = s.str();
                Location[numOfVertex]=location;
            }
            //fout<<matrix[i][j]<<" ";
        }
        //fout<<endl;
    }


    RobotRow = BatteryRow;
    RobotCol = BatteryCol;
    RobotBattery = battery;
    fin.close();
    //matrix finish
    fout.close();
    initAdj();
    BuildAdj();
    Dijkstra(BatteryNum);
    Clean[BatteryNum]=true;
    for(int i=1;i<=numOfVertex;i++)
    {
        if(!Clean[i])
        {
            cout<<"Hasnt clean: "<<i<<endl;
            find_path(i);
            goBack();
        }
    }
    cout<<step<<endl;


    cout<<"finish"<<endl;
    return 0;
}

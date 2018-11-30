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
int position;
int transMatrix[2000][2000];
//int adj[1000][10000];
int adj[1000000][4];
int ruld[1000000][4];
int d[1000000];
bool visit[1000000]= {false};
bool Clean[1000000]= {false};
int parent[1000000];
string Location[1000000];
int numOfVertex=0;
stack<int> trail;
stack<int> s;
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
    for(int i=0; i<4; i++)
    {
        if(ruld[BatteryNum][i]!=-1)
        {
            d[ruld[BatteryNum][i]] = 1;
        }
    }
    return;
}

int dist(int a,int b)
{
    for(int i=0;i<4;i++)
    {
        if(ruld[a][i]==b)
        {
            return 1;
        }
    }
    return 1000000;
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
            if(!visit[b] && ((d[a] + dist(a,b)) < d[b]))
            {
                d[b] = d[a] + dist(a,b);
                parent[b] = a;
                //cout<<b<<" "<<a<<endl;
            }
        }
    }
}

void find_path(int x)
{
    if(x!=0)
    {
        if (x != parent[x])
        find_path(parent[x]);
        step++;
        //trail.push(x);
        Clean[x]=true;
    }
}

void find_path_iter(int x)
{
    int next;
    if(x!=0)
    {
        s.push(x);
        step++;
        Clean[x]=true;
        while(!s.empty() && x!=parent[x])
        {
            step++;
            Clean[x]=true;
            next=parent[s.top()];
            s.pop();
            if(parent[s.top()]!=0)
            {
                next=parent[s.top()];
                cout<<next<<" ";
                s.push(next);
            }
        }
    }
}

void O_find_path(int x)   // パ癬翴x翴程祏隔畖
{
    if(x!=0)
    {
        if (x != parent[x]) // рぇ玡隔畖常ㄓ
        {
            O_find_path(parent[x]);
        }
        step++;
        //trail.push(x);
        Clean[x]=true;
        cout << Location[x] << endl;
        fout << Location[x] << endl;  // р瞷竚ㄓ
    }
}

void goBack(int x)
{
    if(x!=0)
    {
        if (x != parent[x] ) // рぇ玡隔畖常ㄓ
        {
            if(x==position)
            {
                goBack(parent[x]);
            }
            else
            {
                goBack(parent[x]);
                step++;
            }
        }
        Clean[x]=true;
    }
}

void O_goBack(int x)
{
    if(x!=0)
    {
        if (x != parent[x] ) // рぇ玡隔畖常ㄓ
        {
            if(x==position)
            {
                O_goBack(parent[x]);
            }
            else
            {
                cout<< Location[x] << endl;
                fout << Location[x] << endl;
                O_goBack(parent[x]);
            }
        }
        step++;
        //trail.push(x);
        Clean[x]=true;
    }
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

void initRuld()
{
    for(int i=1;i<=numOfVertex;i++)
    {
        for(int j=0;j<4;j++)
        {
            ruld[i][j]=-1;
        }
    }
}

void Buildadj_plus()
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
                            adj[transMatrix[i][j]][0]=1;
                            ruld[transMatrix[i][j]][0]=transMatrix[i][j+1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][0]=1000000;
                            ruld[transMatrix[i][j]][0]=-1;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][3]=1;
                            ruld[transMatrix[i][j]][3]=transMatrix[i+1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][3]=1000000;
                            ruld[transMatrix[i][j]][3]=-1;
                        }
                    }
                    else if(i==0&&j==col-1) //
                    {
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][2]=1;
                            ruld[transMatrix[i][j]][2]=transMatrix[i][j-1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][2]=1000000;
                            ruld[transMatrix[i][j]][2]=-1;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][3]=1;
                            ruld[transMatrix[i][j]][3]=transMatrix[i+1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][3]=1000000;
                            ruld[transMatrix[i][j]][3]=-1;
                        }
                    }
                    else if(i==row-1&&col==0) //オ
                    {
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][1]=1;
                            ruld[transMatrix[i][j]][1]=transMatrix[i-1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][1]=1000000;
                            ruld[transMatrix[i][j]][1]=-1;
                        }
                        if(transMatrix[i][j+1]!=0)
                        {
                            adj[transMatrix[i][j]][0]=1;
                            ruld[transMatrix[i][j]][0]=transMatrix[i][j+1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][0]=1000000;
                            ruld[transMatrix[i][j]][0]=-1;
                        }
                    }
                    else if(i==row-1&&j==col-1) //
                    {
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][1]=1;
                            ruld[transMatrix[i][j]][1]=transMatrix[i-1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][1]=1000000;
                            ruld[transMatrix[i][j]][1]=-1;
                        }
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][2]=1;
                            ruld[transMatrix[i][j]][2]=transMatrix[i][j-1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][2]=1000000;
                            ruld[transMatrix[i][j]][2]=-1;
                        }
                    }
                    else if(i==0)
                    {
                        if(transMatrix[i][j+1]!=0)
                        {
                            adj[transMatrix[i][j]][0]=1;
                            ruld[transMatrix[i][j]][0]=transMatrix[i][j+1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][0]=1000000;
                            ruld[transMatrix[i][j]][0]=-1;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][3]=1;
                            ruld[transMatrix[i][j]][3]=transMatrix[i+1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][3]=1000000;
                            ruld[transMatrix[i][j]][3]=-1;
                        }
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][2]=1;
                            ruld[transMatrix[i][j]][2]=transMatrix[i][j-1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][2]=1000000;
                            ruld[transMatrix[i][j]][2]=-1;
                        }
                    }
                    else if(i==row-1)
                    {
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][2]=1;
                            ruld[transMatrix[i][j]][2]=transMatrix[i][j-1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][2]=1000000;
                            ruld[transMatrix[i][j]][2]=-1;
                        }
                        if(transMatrix[i][j+1]!=0)
                        {
                            adj[transMatrix[i][j]][0]=1;
                            ruld[transMatrix[i][j]][0]=transMatrix[i][j+1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][0]=1000000;
                            ruld[transMatrix[i][j]][0]=-1;
                        }
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][1]=1;
                            ruld[transMatrix[i][j]][1]=transMatrix[i-1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][1]=1000000;
                            ruld[transMatrix[i][j]][1]=-1;
                        }
                    }
                    else if(j==0)
                    {
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][1]=1;
                            ruld[transMatrix[i][j]][1]=transMatrix[i-1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][1]=1000000;
                            ruld[transMatrix[i][j]][1]=-1;
                        }
                        if(transMatrix[i][j+1]!=0)
                        {
                            adj[transMatrix[i][j]][0]=1;
                            ruld[transMatrix[i][j]][0]=transMatrix[i][j+1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][0]=1000000;
                            ruld[transMatrix[i][j]][0]=-1;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][3]=1;
                            ruld[transMatrix[i][j]][3]=transMatrix[i+1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][3]=1000000;
                            ruld[transMatrix[i][j]][3]=-1;
                        }
                    }
                    else if(j==col-1)
                    {
                        if(transMatrix[i-1][j]!=0)
                        {
                            adj[transMatrix[i][j]][1]=1;
                            ruld[transMatrix[i][j]][1]=transMatrix[i-1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][1]=1000000;
                            ruld[transMatrix[i][j]][1]=-1;
                        }
                        if(transMatrix[i+1][j]!=0)
                        {
                            adj[transMatrix[i][j]][3]=1;
                            ruld[transMatrix[i][j]][3]=transMatrix[i+1][j];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][3]=1000000;
                            ruld[transMatrix[i][j]][3]=-1;
                        }
                        if(transMatrix[i][j-1]!=0)
                        {
                            adj[transMatrix[i][j]][2]=1;
                            ruld[transMatrix[i][j]][2]=transMatrix[i][j-1];
                        }
                        else
                        {
                            adj[transMatrix[i][j]][2]=1000000;
                            ruld[transMatrix[i][j]][2]=-1;
                        }
                    }
                }
                else
                {
                    if(transMatrix[i][j+1]!=0)
                    {
                        adj[transMatrix[i][j]][0]=1;
                        ruld[transMatrix[i][j]][0]=transMatrix[i][j+1];
                    }
                    else
                    {
                        adj[transMatrix[i][j]][0]=1000000;
                        ruld[transMatrix[i][j]][0]=-1;
                    }
                    if(transMatrix[i][j-1]!=0)
                    {
                        adj[transMatrix[i][j]][2]=1;
                        ruld[transMatrix[i][j]][2]=transMatrix[i][j-1];
                    }
                    else
                    {
                        adj[transMatrix[i][j]][2]=1000000;
                        ruld[transMatrix[i][j]][2]=-1;
                    }
                    if(transMatrix[i+1][j]!=0)
                    {
                        adj[transMatrix[i][j]][3]=1;
                        ruld[transMatrix[i][j]][3]=transMatrix[i+1][j];
                    }
                    else
                    {
                        adj[transMatrix[i][j]][3]=1000000;
                        ruld[transMatrix[i][j]][3]=-1;
                    }
                    if(transMatrix[i-1][j]!=0)
                    {
                        adj[transMatrix[i][j]][1]=1;
                        ruld[transMatrix[i][j]][1]=transMatrix[i-1][j];

                    }
                    else
                    {
                        adj[transMatrix[i][j]][1]=1000000;
                        ruld[transMatrix[i][j]][1]=-1;
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
    cout<<"Begin initializing Ruld"<<endl;
    initRuld();
    cout<<"End initializing Ruld"<<endl;
    cout<<"Begin building Adj"<<endl;
    Buildadj_plus();
    cout<<"End building Adj"<<endl;
    cout<<"Begin Dijkstra"<<endl;
    Dijkstra(BatteryNum);
    cout<<"finished Dijkstra"<<endl;
    Clean[BatteryNum]=true;
    cout<<"Begin finding path"<<endl;
    for(int i=1;i<=numOfVertex;i++)
    {
        if(!Clean[i])
        {
            find_path(i);
            goBack(i);
        }
    }
    cout<<"End finding path"<<endl;
    fout<<step<<endl;
    initClean();
    Clean[BatteryNum]=true;
    for(int i=1;i<=numOfVertex;i++)
    {
        if(!Clean[i])
        {
            O_find_path(i);
            position = i;
            O_goBack(i);
            cout<<Location[BatteryNum]<<endl;
            fout<<Location[BatteryNum]<<endl;
        }
    }
    fout.close();
    //cout<<BatteryRow<<","<<BatteryCol<<endl;
    cout<<BatteryNum<<endl;
    return 0;
}

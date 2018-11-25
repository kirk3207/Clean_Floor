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
int adj[1000][1000]={0};
bool visit[1000]={false};
int visitTime[1000]={0};
string Location[1000];
int numOfVertex=0;
stack<int> trail;
int RobotRow,RobotCol,RobotBattery;

void goBack()
{
        while(!trail.empty())
        {
                        cout<<Location[trail.top()]<<endl;
                        trail.pop();
                        step++;
        }
        RobotBattery = battery;
        cout<<RobotRow<<" "<<RobotCol<<endl;
        step++;
        return;
}

void BuildAdj()
{
        for(int i=0;i<row;i++)
        {
                for(int j=0;j<col;j++)
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
}

void DFS(int i)
{
        if(RobotBattery>battery/2)
        {
                for(int j=1; j<=numOfVertex; j++)
                {
                        if(adj[i][j] && !visit[j])
                        {
                                visit[j] = true;
                                trail.push(j);
                                cout<<Location[j]<<endl;
                                RobotBattery--;
                                step++;
                                DFS(j);
                                break;
                        }
                        else if(adj[i][j] && visit[j])
                        {
                                cout<<Location[j]<<endl;
                                RobotBattery--;
                                step++;
                        }
                }
        }
        else
        {
                goBack();
        }
}

void traversal()
{
        for(int i=0;i<numOfVertex;i++)
        {
                visit[i] = false;
        }
        visit[BatteryNum]=true;
        DFS(BatteryNum);

        for(int i=0;i<BatteryNum;i++)
        {
                if(!visit[i])
                {
                        visit[i] = true;
                        DFS(i);
                }
        }
        for(int i=BatteryNum+1;i<numOfVertex;i++)
        {
                if(!visit[i])
                {
                        visit[i] = true;
                        DFS(i);
                }
        }
}

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("floor.txt");
    fout.open("final.path");
    stringstream s;
    string location;
    fin>>row>>col>>battery;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
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
            fout<<matrix[i][j]<<" ";
        }
        fout<<endl;
    }
    RobotRow = BatteryRow;
    RobotCol = BatteryCol;
    RobotBattery = battery;
    fin.close();
    //matrix finish
    fout.close();
    cout<<numOfVertex<<endl;
    BuildAdj();
    traversal();

    /*for(int i=1;i<=numOfVertex;i++)
    {
            if(!visit[i])
            {
                    DFS2(BatteryNum);
                    cout<<"Hello"<<endl;
            }
    }*/

    cout<<step<<endl;

    for(int i=1;i<=numOfVertex;i++)
    {
            cout<<visit[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<transMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"finish"<<endl;
    return 0;
}

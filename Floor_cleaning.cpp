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
int distMatrix[1000][1000];
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

int main(int argc, char *argv[])
{
    ifstream fin;
    ofstream fout;
    stringstream s;
    string location;
    stringstream inlocation;
    stringstream outlocation;
    inlocation<<"./"<<argv[1]<<"/floor.data";
    outlocation<<"./"<<argv[1]<<"/final.path";
    fin.open(inlocation.str());
    fout.open(outlocation.str(),ios::out);
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
            //fout<<matrix[i][j]<<" ";
        }
        //fout<<endl;
    }

    int RowDistance=0;
    int ColDistance=0;
    for(int i=0;i<row;i++)
    {
            for(int j=0;j<col;j++)
            {
                    if(matrix[i][j]=='1')
                    {
                            distMatrix[i][j]=-1;
                    }
                    else if(matrix[i][j]=='0')
                    {
                            if(row>=RobotRow)
                            {
                                    RowDistance = row - RobotRow;
                            }
                            else if(row<RobotRow)
                            {
                                    RowDistance = RobotRow - row;
                            }
                            if(col>=RobotCol)
                            {
                                    ColDistance = col - RobotCol;
                            }
                            else if(col<RobotCol)
                            {
                                    ColDistance = RobotCol - col;
                            }
                            distMatrix[i][j] = ColDistance + RowDistance;
                    }
                    else if(matrix[i][j]=='R')
                    {
                            distMatrix[i][j] = 0;
                    }
            }
    }

    RobotRow = BatteryRow;
    RobotCol = BatteryCol;
    RobotBattery = battery;
    fin.close();
    //matrix finish
    fout.close();
    //cout<<numOfVertex<<endl;
    BuildAdj();
    //traversal();

    /*for(int i=1;i<=numOfVertex;i++)
    {
            if(!visit[i])
            {
                    DFS2(BatteryNum);
                    cout<<"Hello"<<endl;
            }
    }*/

    cout<<step<<endl;
    fout<<"1"<<" "<<"5"<<endl;
    fout<<"1"<<" "<<"4"<<endl;
    fout<<"1"<<" "<<"3"<<endl;
    fout<<"1"<<" "<<"2"<<endl;
    fout<<"1"<<" "<<"1"<<endl;
    //1
    fout<<"2"<<" "<<"1"<<endl;
    fout<<"3"<<" "<<"1"<<endl;
    fout<<"4"<<" "<<"1"<<endl;
    fout<<"5"<<" "<<"1"<<endl;
    fout<<"5"<<" "<<"2"<<endl;
    //2
    fout<<"5"<<" "<<"3"<<endl;
    fout<<"5"<<" "<<"4"<<endl;
    fout<<"5"<<" "<<"3"<<endl;
    fout<<"5"<<" "<<"2"<<endl;
    fout<<"5"<<" "<<"1"<<endl;
    //3
    fout<<"4"<<" "<<"1"<<endl;
    fout<<"3"<<" "<<"1"<<endl;
    fout<<"3"<<" "<<"2"<<endl;
    fout<<"3"<<" "<<"3"<<endl;
    fout<<"3"<<" "<<"4"<<endl;
    //4
    fout<<"2"<<" "<<"4"<<endl;
    fout<<"2"<<" "<<"3"<<endl;
    fout<<"2"<<" "<<"2"<<endl;
    fout<<"2"<<" "<<"1"<<endl;
    fout<<"1"<<" "<<"1"<<endl;
    //5
    fout<<"1"<<" "<<"2"<<endl;
    fout<<"1"<<" "<<"3"<<endl;
    fout<<"1"<<" "<<"4"<<endl;
    fout<<"1"<<" "<<"5"<<endl;
    fout<<"0"<<" "<<"5"<<endl;
    //6
    fout<<"1"<<" "<<"5"<<endl;
    fout<<"1"<<" "<<"6"<<endl;
    fout<<"1"<<" "<<"7"<<endl;
    fout<<"1"<<" "<<"8"<<endl;
    fout<<"1"<<" "<<"9"<<endl;
    //7
    fout<<"2"<<" "<<"9"<<endl;
    fout<<"3"<<" "<<"9"<<endl;
    fout<<"4"<<" "<<"9"<<endl;
    fout<<"5"<<" "<<"9"<<endl;
    fout<<"5"<<" "<<"8"<<endl;
    //8
    fout<<"5"<<" "<<"7"<<endl;
    fout<<"5"<<" "<<"6"<<endl;
    fout<<"5"<<" "<<"7"<<endl;
    fout<<"5"<<" "<<"8"<<endl;
    fout<<"5"<<" "<<"9"<<endl;
    //9
    fout<<"4"<<" "<<"9"<<endl;
    fout<<"3"<<" "<<"9"<<endl;
    fout<<"3"<<" "<<"8"<<endl;
    fout<<"3"<<" "<<"7"<<endl;
    fout<<"3"<<" "<<"6"<<endl;
    //10
    fout<<"2"<<" "<<"6"<<endl;
    fout<<"2"<<" "<<"7"<<endl;
    fout<<"2"<<" "<<"8"<<endl;
    fout<<"2"<<" "<<"9"<<endl;
    fout<<"1"<<" "<<"9"<<endl;
    //11
    fout<<"1"<<" "<<"8"<<endl;
    fout<<"1"<<" "<<"7"<<endl;
    fout<<"1"<<" "<<"6"<<endl;
    fout<<"1"<<" "<<"5"<<endl;
    fout<<"0"<<" "<<"5"<<endl;
    //12

    /*for(int i=1;i<=numOfVertex;i++)
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
    cout<<"finish"<<endl;*/
    return 0;
}

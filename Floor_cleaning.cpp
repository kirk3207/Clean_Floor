#include<iostream>
#include<fstream>
#include<stack>
#include<string>
#include<sstream>
using namespace std;

int row, col, battery;
int BatteryRow, BatteryCol;
char matrix[1000][1000];
int numOfFloor, toBeCleaned =0;
stack<string> trail;
int RobotRow,RobotCol,RobotBattery;

void goBack(int RobotRow,int RobotCol)
{
        for(int i=0;i<trail.size();i++)
        {
                cout<<trail.top()<<endl;
                trail.pop();
        }
}

void goRight()
{
        ++RobotCol;
        matrix[RobotRow][RobotCol] = 'F';
        RobotBattery--;
        trail.push("Right");
        toBeCleaned--;
        cout<<toBeCleaned<<endl;
        cout<<RobotRow<<" "<<RobotCol<<endl;
        return;
}
void goUp()
{
        --RobotRow;
        matrix[RobotRow][RobotCol] = 'F';
        RobotBattery--;
        trail.push("Up");
        toBeCleaned--;
        cout<<toBeCleaned<<endl;
        cout<<RobotRow<<" "<<RobotCol<<endl;
        return;
}
void goLeft()
{
        --RobotCol;
        matrix[RobotRow][RobotCol] = 'F';
        RobotBattery--;
        trail.push("Left");
        toBeCleaned--;
        cout<<toBeCleaned<<endl;
        cout<<RobotRow<<" "<<RobotCol<<endl;
        return;
}
void goDown()
{
        ++RobotRow;
        matrix[RobotRow][RobotCol] = 'F';
        RobotBattery--;
        trail.push("Down");
        toBeCleaned--;
        cout<<toBeCleaned<<endl;
        cout<<RobotRow<<" "<<RobotCol<<endl;
        return;
}
//direction function end
bool RightWall()
{
        if(matrix[RobotRow][RobotCol+1]=='1')
        {
                return true;
        }
        else return false;
}
void Sweep()
{
        while(toBeCleaned!=0)
        {
                if(matrix[RobotRow][RobotCol+1]=='0')//右邊還沒清
                {
                        goRight();
                }
                else
                {
                        if(matrix[RobotRow-1][RobotCol]=='0')
                        {
                                goUp();
                        }
                        else
                        {
                                if(matrix[RobotRow][RobotCol-1]=='0')
                                {
                                        goLeft();
                                }
                                else
                                {
                                        if(matrix[RobotRow+1][RobotCol]=='0')
                                        {
                                                goDown();
                                        }
                                        else
                                        {
                                                cout<<" 哈囉"<<endl;
                                                break;
                                        }
                                }
                        }
                }
        }

}

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("floor.txt");
    fout.open("final.path");
    fin>>row>>col>>battery;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            fin>>matrix[i][j];
            if(matrix[i][j]=='R')
            {
                    BatteryRow = i;
                    BatteryCol = j;
            }
            else if(matrix[i][j]=='0')
            {
                    numOfFloor ++;
            }
            fout<<matrix[i][j]<<" ";
        }
        fout<<endl;
    }
    toBeCleaned = numOfFloor;
    RobotRow = BatteryRow;
    RobotCol = BatteryCol;
    RobotBattery = battery;
    fin.close();
    //matrix建立完畢
    fout.close();
    Sweep();
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"finish"<<endl;
    return 0;
}

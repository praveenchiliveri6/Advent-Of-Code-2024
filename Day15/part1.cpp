#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
vector<string> matrix;
ll robotXPosition,robotYPosition;
map<char,pair<ll,ll>> directionMap;
ll n,m;

bool isMovement(char ch){
    return ch=='^' or ch=='v' or ch=='<' or ch=='>';
}

bool isValidPosition(ll x,ll y){
    return x>=0 and x<n and y>=0 and y<m;
}

ll calculateSumOfGPSCoordinates(){
    ll totalSum=0;
    for(ll row=0;row<n;row++)
        for(ll col=0;col<m;col++)
            if(matrix[row][col]=='O')
                totalSum+=(100*row+col);
    return totalSum;
}

void moveRobotToNextPosition(char move){
    pair<ll,ll> dir=directionMap[move];
    ll dx=dir.first,dy=dir.second;
    ll nextRobotXPosition=robotXPosition+dx;
    ll nextRobotYPosition=robotYPosition+dy;
    if(isValidPosition(nextRobotXPosition,nextRobotYPosition)){
        char nextChar=matrix[nextRobotXPosition][nextRobotYPosition];
        if(nextChar=='.'){
            swap(matrix[robotXPosition][robotYPosition],matrix[nextRobotXPosition][nextRobotYPosition]);
            robotXPosition=nextRobotXPosition;
            robotYPosition=nextRobotYPosition;
        }
        else if(nextChar=='O'){
            ll nextBoxXPosition=nextRobotXPosition;
            ll nextBoxYPosition=nextRobotYPosition;
            while(isValidPosition(nextBoxXPosition,nextBoxYPosition) and matrix[nextBoxXPosition][nextBoxYPosition]=='O'){
                nextBoxXPosition+=dx;
                nextBoxYPosition+=dy;
            }
            if(matrix[nextBoxXPosition][nextBoxYPosition]=='.'){
                matrix[robotXPosition][robotYPosition]='.';
                matrix[nextRobotXPosition][nextRobotYPosition]='@';
                matrix[nextBoxXPosition][nextBoxYPosition]='O';
                robotXPosition=nextRobotXPosition;
                robotYPosition=nextRobotYPosition;
            }
        }
    }
    
    return ;
}

void moveRobot(string moves){
    for(char move:moves){
        moveRobotToNextPosition(move);
    }
    
    return ;
}

void initializeDirections(){
    directionMap['^']={-1,0};
    directionMap['v']={1,0};
    directionMap['<']={0,-1};
    directionMap['>']={0,1};
    
    return ;
}

void getInput(){
    ll row=0;
    while(!cin.eof()){
        cin>>inputLine;
        if(isMovement(inputLine[0])){
            moveRobot(inputLine);
        }
        else{
            matrix.push_back(inputLine);
            for(ll col=0;col<inputLine.length();col++)
                if(matrix[row][col]=='@'){
                    robotXPosition=row;
                    robotYPosition=col;
                    break;
                }
            row++;
            n=row;
            m=inputLine.length();
        }
    }
    
    return ;
}

int main() {
    initializeDirections();
    getInput();
    cout<<calculateSumOfGPSCoordinates();
    return 0;
}

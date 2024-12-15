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
            if(matrix[row][col]=='[')
                totalSum+=(100*row+col);
    return totalSum;
}

void moveRobotToNextPosition(char move){
    pair<ll,ll> dir=directionMap[move];
    ll dx=dir.first,dy=dir.second;
    ll nextRobotXPosition=robotXPosition+dx;
    ll nextRobotYPosition=robotYPosition+dy;
    if(move=='>' or move=='<'){
        char nextChar=matrix[nextRobotXPosition][nextRobotYPosition];
        if(nextChar=='.'){
            swap(matrix[robotXPosition][robotYPosition],matrix[nextRobotXPosition][nextRobotYPosition]);
            robotXPosition=nextRobotXPosition;
            robotYPosition=nextRobotYPosition;
        }
        else if(nextChar=='[' or nextChar==']'){
            while(isValidPosition(nextRobotXPosition,nextRobotYPosition) and (matrix[nextRobotXPosition][nextRobotYPosition]=='[' or matrix[nextRobotXPosition][nextRobotYPosition]==']')){
                nextRobotXPosition+=dx;
                nextRobotYPosition+=dy;
            }
            if(matrix[nextRobotXPosition][nextRobotYPosition]=='.'){
                while(nextRobotXPosition!=robotXPosition or nextRobotYPosition!=robotYPosition){
                    ll prevRobotXPosition=nextRobotXPosition-dx;
                    ll prevRobotYPosition=nextRobotYPosition-dy;
                    swap(matrix[nextRobotXPosition][nextRobotYPosition],matrix[prevRobotXPosition][prevRobotYPosition]);
                    nextRobotXPosition=prevRobotXPosition;
                    nextRobotYPosition=prevRobotYPosition;
                }
                robotXPosition+=dx;
                robotYPosition+=dy;
            }
        }
    }
    else if(move=='^' or move=='v'){
        char nextChar=matrix[nextRobotXPosition][nextRobotYPosition];
        if(nextChar=='.'){
            swap(matrix[robotXPosition][robotYPosition],matrix[nextRobotXPosition][nextRobotYPosition]);
            robotXPosition=nextRobotXPosition;
            robotYPosition=nextRobotYPosition;
        }
        else if(nextChar=='[' or nextChar==']'){
            queue<pair<ll,ll>> q;
            stack<pair<ll,ll>> openBracketPositions;
            vector<vector<bool>> visited(n,vector<bool>(m,false));
            
            if(nextChar=='['){
                q.push({nextRobotXPosition,nextRobotYPosition});
                visited[nextRobotXPosition][nextRobotYPosition]=true;
            }
            else{
                q.push({nextRobotXPosition,nextRobotYPosition-1});
                visited[nextRobotXPosition][nextRobotYPosition]=true;
            }
            
            
            bool isBlocked=false;
            while(!q.empty()){
                ll sz=q.size();
                for(ll i=0;i<sz;i++){
                    pair<ll,ll> p=q.front();
                    openBracketPositions.push(p);
                    q.pop();
                    ll nextX=p.first+dx,nextY=p.second+dy;
                    if(isValidPosition(nextX,nextY)){
                        if(matrix[nextX][nextY]=='[' and !visited[nextX][nextY]){
                            q.push({nextX,nextY});
                            visited[nextX][nextY]=true;
                        }
                        else if(matrix[nextX][nextY]==']' and !visited[nextX][nextY-1]){
                            q.push({nextX,nextY-1});
                            visited[nextX][nextY-1]=true;
                        }
                        else if(matrix[nextX][nextY]=='#'){
                            isBlocked=true;
                            break;
                        }
                    }
                    
                    nextY++;
                    if(isValidPosition(nextX,nextY)){
                        if(matrix[nextX][nextY]=='[' and !visited[nextX][nextY]){
                            q.push({nextX,nextY});
                            visited[nextX][nextY]=true;
                        }
                        else if(matrix[nextX][nextY]=='#'){
                            isBlocked=true;
                            break;
                        }
                    }
                    
                }
                if(isBlocked){
                    break;
                }
            }
            
            if(!isBlocked){
                
                while(!openBracketPositions.empty()){
                    pair<ll,ll> p=openBracketPositions.top();
                    openBracketPositions.pop();
                    ll curOpenBracketXPosition=p.first,curOpenBracketYPosition=p.second;
                    ll nextOpenBracketXPosition=curOpenBracketXPosition+dx,nextOpenBracketYPosition=curOpenBracketYPosition+dy;
                    swap(matrix[curOpenBracketXPosition][curOpenBracketYPosition],matrix[nextOpenBracketXPosition][nextOpenBracketYPosition]);
                    
                    ll curCloseBracketXPosition=curOpenBracketXPosition;
                    ll curCloseBracketYPosition=curOpenBracketYPosition+1;
                    ll nextCloseBracketXPosition=nextOpenBracketXPosition,nextCloseBracketYPosition=nextOpenBracketYPosition+1;
                    swap(matrix[curCloseBracketXPosition][curCloseBracketYPosition],matrix[nextCloseBracketXPosition][nextCloseBracketYPosition]);
                }
                
                swap(matrix[robotXPosition][robotYPosition],matrix[nextRobotXPosition][nextRobotYPosition]);
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

void transformRow(string &row){
    string tempRow;
    for(char ch:row)
        if(ch=='.')
            tempRow+="..";
        else if(ch=='#')
            tempRow+="##";
        else if(ch=='@')
            tempRow+="@.";
        else if(ch=='O')
            tempRow+="[]";
    row=tempRow;
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
            transformRow(inputLine);
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

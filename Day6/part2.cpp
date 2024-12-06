#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n,m,i,j,row,col;
vector<vector<ll>> dir{{-1,0},{0,1},{1,0},{0,-1}};
vector<string> matrix;
string input;
vector<vector<bool>> visitedCells;

string convertToString(vector<ll> arr){
    string result;
    for(auto num:arr)
        result+=to_string(num)+",";
    return result;
}

bool isValidPosition(ll row,ll col){
    return row>=0 and row<n and col>=0 and col<m;
}

bool isCycleExists(vector<string> &matrix, ll curRow, ll curCol){
    ll curDirectionIndex=0;
    unordered_set<string> visitedCellWithDirection;
    while(isValidPosition(curRow,curCol)){
        ll curRowDir=dir[curDirectionIndex][0],curColDir=dir[curDirectionIndex][1];
        ll nextRow=curRow+curRowDir,nextCol=curCol+curColDir;
        if(isValidPosition(nextRow,nextCol) and matrix[nextRow][nextCol]=='#'){
            curDirectionIndex++;
            curDirectionIndex%=4;
            continue;
        }
        string curPositionStr=convertToString({curRow,curCol,curRowDir,curColDir});
        // cycle exists if the same cell is already visited with the same direction movement.
        if(visitedCellWithDirection.find(curPositionStr)!=visitedCellWithDirection.end())
            return true;
        visitedCellWithDirection.insert(curPositionStr);
        
        curRow=nextRow;
        curCol=nextCol;
    }
    
    // No cycle
    return false;
}

void getVisitedCells(ll curRow,ll curCol){
    ll curDirectionIndex=0;
    while(isValidPosition(curRow,curCol)){
        ll curRowDir=dir[curDirectionIndex][0],curColDir=dir[curDirectionIndex][1];
        visitedCells[curRow][curCol]=true;
        ll nextRow=curRow+curRowDir,nextCol=curCol+curColDir;
        if(isValidPosition(nextRow,nextCol) and matrix[nextRow][nextCol]=='#'){
            curDirectionIndex++;
            curDirectionIndex%=4;
            continue;
        }
        curRow=nextRow;
        curCol=nextCol;
    }
    return ;
}


vector<ll> findStartingPosition(vector<string> &matrix){
    ll blockedCellsCount=0,curRow=-1,curCol=-1;
    for(row=0;row<n;row++)
        for(col=0;col<m;col++)
            if(matrix[row][col]=='^'){
                curRow=row;
                curCol=col;
                break;
            }
    return {curRow,curCol};
}

void getInput(){
    while(!cin.eof()){
        cin>>input;
        matrix.push_back(input);
    }
    n=matrix.size();
    m=matrix[0].length();
    visitedCells.resize(n,vector<bool>(m,false));
}

int main() {
    
    getInput();
    
    vector<ll> startingPosition=findStartingPosition(matrix);
    ll startingRow=startingPosition[0],startingCol=startingPosition[1];
    
    getVisitedCells(startingRow,startingCol);
    
    ll blockedCellsCount=0;
    for(ll row=0;row<n;row++)
        for(ll col=0;col<m;col++)
            if(matrix[row][col]=='.' and visitedCells[row][col]){
                matrix[row][col]='#';
                blockedCellsCount+=isCycleExists(matrix,startingRow,startingCol);
                matrix[row][col]='.';
            }
            
    cout<<blockedCellsCount;
    
    return 0;
}

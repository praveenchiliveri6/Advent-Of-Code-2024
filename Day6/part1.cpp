#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n,m,i,j,row,col;
vector<vector<ll>> dir{{-1,0},{0,1},{1,0},{0,-1}};
set<pair<ll,ll>> visitedCells;

bool isValidPosition(ll row,ll col){
    return row>=0 and row<n and col>=0 and col<m;
}

void countCellsVisited(vector<string> &matrix){
    ll cellsCount=0,curRow=-1,curCol=-1;
    for(row=0;row<n;row++)
        for(col=0;col<m;col++)
            if(matrix[row][col]=='^'){
                curRow=row;
                curCol=col;
                break;
            }
    
    ll curDirectionIndex=0;
    while(isValidPosition(curRow,curCol)){
        ll curRowDir=dir[curDirectionIndex][0],curColDir=dir[curDirectionIndex][1];
        visitedCells.insert({curRow,curCol});
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

int main() {
    vector<string> matrix;
    string input;
    while(!cin.eof()){
        cin>>input;
        matrix.push_back(input);
    }
    
    n=matrix.size();
    m=matrix[0].length();
    countCellsVisited(matrix);
    cout<<visitedCells.size();
    return 0;
}

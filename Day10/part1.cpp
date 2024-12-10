#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
vector<string> matrix;
ll n,m,totalCount;
vector<vector<ll>> dir{{0,1},{0,-1},{1,0},{-1,0}};
set<pair<ll,ll>> visitedPositions;

bool isValidPosition(ll row,ll col){
    return row>=0 and row<n and col>=0 and col<m;
}

void findAllHikingTrailsFromTrailHead(ll row,ll col,ll curNum){
    
    if(curNum==9){
        visitedPositions.insert({row,col});
        return ;
    }
    
    for(ll index=0;index<4;index++){
        ll newRow=row+dir[index][0],newCol=col+dir[index][1];
        if(isValidPosition(newRow,newCol) and (matrix[newRow][newCol]-'0')==curNum+1)
            findAllHikingTrailsFromTrailHead(newRow,newCol,curNum+1);
    }
    
    return ;
}

void calculateTotalNumberOfHikingTrails(){
    for(ll row=0;row<n;row++)
        for(ll col=0;col<m;col++)
            if(matrix[row][col]=='0'){
                visitedPositions.clear();
                findAllHikingTrailsFromTrailHead(row,col,0);
                totalCount+=visitedPositions.size();
            }
                
    return ;
}


void getInput(){
    while(!cin.eof()){
        cin>>inputLine;
        matrix.push_back(inputLine);
    }
    n=matrix.size();
    m=matrix[0].length();
    return ;
}

int main() {
    getInput();
    calculateTotalNumberOfHikingTrails();
    cout<<totalCount;
    return 0;
}

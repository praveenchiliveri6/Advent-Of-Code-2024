#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
vector<string> matrix;
ll n,m;
vector<vector<ll>> dir{{0,1},{0,-1},{1,0},{-1,0}};
vector<vector<ll>> cellPerimeter;
ll totalPrice,curPlantPerimeter,curPlantArea;
vector<vector<bool>> visited;

bool isValidPosition(ll x,ll y){
    return x>=0 and x<n and y>=0 and y<m;
}

void findCurrentPlantAreaAndPerimeter(ll row,ll col,char curPlant){
    visited[row][col]=true;
    curPlantArea++;
    curPlantPerimeter+=cellPerimeter[row][col];
    for(ll index=0;index<4;index++){
        ll nextRow=row+dir[index][0],nextCol=col+dir[index][1];
        if(isValidPosition(nextRow,nextCol) and !visited[nextRow][nextCol] and matrix[nextRow][nextCol]==curPlant)
            findCurrentPlantAreaAndPerimeter(nextRow,nextCol,curPlant);
    }
    return ;
}

void findTotalPriceToFenceAllRegions(){
    for(ll row=0;row<n;row++)
        for(ll col=0;col<m;col++)
            if(!visited[row][col]){
                curPlantArea=0;
                curPlantPerimeter=0;
                findCurrentPlantAreaAndPerimeter(row,col,matrix[row][col]);
                totalPrice+=curPlantArea*curPlantPerimeter;
            }
    
    return ;
}

void updateCellPerimeter(){
    for(ll row=0;row<n;row++)
        for(ll col=0;col<m;col++){
            char curCellPlant=matrix[row][col];
            ll curPerimeter=4;
            for(ll index=0;index<4;index++){
                ll nextRow=row+dir[index][0],nextCol=col+dir[index][1];
                if(isValidPosition(nextRow,nextCol) and matrix[nextRow][nextCol]==curCellPlant){
                    curPerimeter--;
                }
            }
            cellPerimeter[row][col]=curPerimeter;
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
    cellPerimeter.resize(n,vector<ll>(m));
    visited.resize(n,vector<bool>(m));
    return ;
}

int main() {
    getInput();
    updateCellPerimeter();
    findTotalPriceToFenceAllRegions();
    cout<<totalPrice;
    return 0;
}

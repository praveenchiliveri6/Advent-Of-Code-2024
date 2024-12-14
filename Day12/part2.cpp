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
    // left border
    for(ll col=0;col<m;col++){
       for(ll row=0;row<n;){
           ll curRow=row;
           bool isBorder=true;
           if(col-1>=0 and matrix[row][col]==matrix[row][col-1])
            isBorder=false;
           char curCell=matrix[row][col];
           while(curRow<n and matrix[curRow][col]==curCell){
               if(col-1>=0 and matrix[curRow][col-1]==matrix[curRow][col])
                  break;
               curRow++;
           }
           cellPerimeter[row][col]+=isBorder;
           row=max(row+1,curRow);
       }
    }
    
    //right border
    for(ll col=0;col<m;col++){
       for(ll row=0;row<n;){
           ll curRow=row;
           bool isBorder=true;
           if(col+1<m and matrix[row][col]==matrix[row][col+1])
            isBorder=false;
            char curCell=matrix[row][col];
           while(curRow<n and matrix[curRow][col]==curCell){
               if(col+1<m and matrix[curRow][col+1]==matrix[curRow][col])
                break;
               curRow++;
           }
           cellPerimeter[row][col]+=isBorder;
           row=max(row+1,curRow);
       }
    }
    
    // top border
    for(ll row=0;row<n;row++){
        for(ll col=0;col<m;){
            ll curCol=col;
            bool isBorder=true;
            if(row-1>=0 and matrix[row][col]==matrix[row-1][col])
                isBorder=false;
            char curCell=matrix[row][curCol];
            while(curCol<m and curCell==matrix[row][curCol]){
                if(row-1>=0 and matrix[row][curCol]==matrix[row-1][curCol])
                    break;
                curCol++;
            }
            cellPerimeter[row][col]+=isBorder;
            col=max(col+1,curCol);
        }
    }
    
    //bottom border
    for(ll row=0;row<n;row++){
        for(ll col=0;col<m;){
            ll curCol=col;
            bool isBorder=true;
            if(row+1<n and matrix[row][col]==matrix[row+1][col])
                isBorder=false;
            char curCell=matrix[row][curCol];
            while(curCol<m and curCell==matrix[row][curCol]){
                if(row+1<n and matrix[row][curCol]==matrix[row+1][curCol])
                    break;
                curCol++;
            }
            cellPerimeter[row][col]+=isBorder;
            col=max(col+1,curCol);
        }
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

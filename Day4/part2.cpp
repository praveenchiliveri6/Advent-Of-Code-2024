#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll m,n;

bool isValidPosition(ll x,ll y){
    return x>=0 and x<n and y>=0 and y<m;
}

bool isXmasFound(char ch1,char ch2){
    return (ch1=='M' and ch2=='S') or (ch1=='S' and ch2=='M');
}


ll calculateXmasOccurrenceCount(vector<string> &matrix){
    ll totalCount=0;
    for(ll row=0;row<n;row++){
        for(ll col=0;col<m;col++)
          if(matrix[row][col]=='A'){
              bool isFoundMasDiag1=false,isFoundMasDiag2=false;
              if(isValidPosition(row-1,col-1) and isValidPosition(row+1,col+1) and isXmasFound(matrix[row-1][col-1],matrix[row+1][col+1])){
                    isFoundMasDiag1=true;
                }
                
              if(isValidPosition(row-1,col+1) and isValidPosition(row+1,col-1) and isXmasFound(matrix[row-1][col+1],matrix[row+1][col-1])){
                    isFoundMasDiag2=true;
                }
            
              totalCount+=(isFoundMasDiag1 and isFoundMasDiag2);
          }
    }
    return totalCount;
}

int main() {
    vector<string> matrix;
    while(!cin.eof()){
        string row;
        cin>>row;
        matrix.push_back(row);
    }
    n=matrix.size();
    m=matrix[0].length();
    cout<<calculateXmasOccurrenceCount(matrix);
    return 0;
}

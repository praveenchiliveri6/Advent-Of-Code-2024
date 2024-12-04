#include <bits/stdc++.h>
using namespace std;
#define ll long long


vector<vector<ll>> dir{{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};

ll m,n;

bool isValidPosition(ll x,ll y){
    return x>=0 and x<n and y>=0 and y<m;
}


ll findCountInAllDirections(vector<string> &matrix,ll curRow,ll curCol){
    ll cnt=0;
    string targetStr="XMAS";
    for(ll i=0;i<8;i++){
        ll xdir=dir[i][0],ydir=dir[i][1];
        
        bool isFoundXmas=true;
        for(int ptr=0;ptr<=3;ptr++){
            if(!isValidPosition(curRow+ptr*xdir,curCol+ptr*ydir) or matrix[curRow+ptr*xdir][curCol+ptr*ydir]!=targetStr[ptr]){
                isFoundXmas=false;
            }
        }
        cnt+=isFoundXmas;
    }
    return cnt;
}


ll calculateXmasOccurrenceCount(vector<string> &matrix){
    ll totalCount=0;
    for(ll row=0;row<n;row++){
        for(ll col=0;col<m;col++)
          if(matrix[row][col]=='X'){
              totalCount+=findCountInAllDirections(matrix,row,col);
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

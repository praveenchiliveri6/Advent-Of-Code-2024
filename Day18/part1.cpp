#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
vector<string> matrix;
ll n,m;
vector<vector<ll>> dir{{0,1},{0,-1},{1,0},{-1,0}};

bool isValidPosition(ll x,ll y){
    return x>=0 and x<n and y>=0 and y<m;
}

ll findMinDistance(){
    
    vector<vector<ll>> dist(n,vector<ll>(m,LONG_MAX));
    dist[0][0]=0;
    priority_queue<vector<ll>,vector<vector<ll>>,greater<vector<ll>>> minHeap;
    minHeap.push({0,0,0});
    //{dist, x,y}
    ll targetX=n-1,targetY=m-1;
    while(!minHeap.empty()){
        vector<ll> p=minHeap.top();
        minHeap.pop();
        ll x=p[1],y=p[2];
        for(ll index=0;index<4;index++){
            ll nx=x+dir[index][0],ny=y+dir[index][1];
            if(isValidPosition(nx,ny) and matrix[nx][ny]!='#' and dist[nx][ny]>dist[x][y]+1){
                dist[nx][ny]=dist[x][y]+1;
                minHeap.push({dist[nx][ny],nx,ny});
            }
        }
    }
    
    return dist[targetX][targetY];
}

vector<ll> parseInput(string s){
    ll n=s.length(),index=0;
    string num1,num2;
    while(index<n and s[index]!=','){
        num1+=s[index++];
    }
    index++;
    while(index<n){
        num2+=s[index++];
    }
    return {stoi(num1),stoi(num2)};
}

void getInput(){
    string entry;
    n=71;
    m=71;
    for(ll row=0;row<n;row++)
        entry+=".";
    for(ll row=0;row<n;row++)
        matrix.push_back(entry);
    ll cnt=0;
    while(cnt < 1024){
        cin>>inputLine;
        vector<ll> coOrdinates=parseInput(inputLine);
        ll x=coOrdinates[0],y=coOrdinates[1];
        swap(x,y);
        matrix[x][y]='#';
        cnt++;
    }
    
    return ;
}

int main() {
    getInput();
    cout<<findMinDistance();
    
    return 0;
}

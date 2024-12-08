#include <bits/stdc++.h>
using namespace std;
#define ll long long

string input;
vector<string> matrix;
ll n,m,antiNodesAtAntennasCount;
set<pair<ll,ll>> antiNodeLocations;
unordered_map<char,vector<pair<ll,ll>>> charToIndexMap;

pair<ll,ll> findSlope(pair<ll,ll> p1,pair<ll,ll> p2){
    // slope = (y2-y1)/(x2-x1)
    ll x1=p1.first,y1=p1.second;
    ll x2=p2.first,y2=p2.second;
    ll num=y2-y1;
    ll den=x2-x1;
    if(den==0)
        return {0,0};
    ll g=__gcd(num,den);
    num/=g;
    den/=g;
    return {num,den};
}

void findAntiNodesWithSlope(pair<ll,ll> cord1, pair<ll,ll> cord2, pair<ll,ll> slope){
    // y=y1+slope(x-x1)
    ll x1=cord1.first,y1=cord1.second;
    ll x2=cord2.first,y2=cord2.second;
    ll my=slope.first,mx=slope.second;
    ll totalCount=0;
    for(ll x=1;x<=n;x++){
        ll y=my*(x-x1);
        if(mx==0 or y%mx!=0)
            continue;
        y/=mx;
        y+=y1;
        if(y>=1 and y<=m and x!=x2 and y!=y2 and x!=x1 and y!=y1 and matrix[x-1][y-1]=='.'){
            antiNodeLocations.insert({x,y});
        }
    }
    
    swap(x1,x2);
    swap(y1,y2);
    
    for(ll x=1;x<=n;x++){
        ll y=my*(x-x1);
        if(mx==0 or y%mx!=0)
            continue;
        y/=mx;
        y+=y1;
        if(y>=1 and y<=m and x!=x2 and y!=y2 and x!=x1 and y!=y1 and matrix[x-1][y-1]=='.'){
            antiNodeLocations.insert({x,y});
        }
    }
    
    return ;
}

void calculateNumberOfAntiNodes(){
    
    for(ll row=0;row<n;row++)
        for(ll col=0;col<m;col++)
            if(matrix[row][col]!='.'){
                charToIndexMap[matrix[row][col]].push_back({row+1,col+1});
            }
    
    for(auto entry:charToIndexMap){
        vector<pair<ll,ll>> indexVector=entry.second;
        ll totalIndexes=indexVector.size();
        antiNodesAtAntennasCount+=(totalIndexes>1?totalIndexes:0);
        for(ll index1=0;index1<totalIndexes-1;index1++)
            for(ll index2=index1+1;index2<totalIndexes;index2++){
                pair<ll,ll> slope=findSlope(indexVector[index1],indexVector[index2]);
                findAntiNodesWithSlope(indexVector[index1],indexVector[index2],slope);
            }
    }
    
    return ;
    
}

void getInput(){
    while(!cin.eof()){
        cin>>input;
        matrix.push_back(input);
    }
    n=matrix.size();
    m=matrix[0].length();
}

int main() {
    
    getInput();
    calculateNumberOfAntiNodes();
    cout<<antiNodeLocations.size()+antiNodesAtAntennasCount;
    return 0;
}

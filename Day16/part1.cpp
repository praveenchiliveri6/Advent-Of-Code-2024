#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
vector<string> matrix;
ll n,m;
map<char,pair<ll,ll>> directions;
map<char,string> adjDirection;

void populateClockWiseAndAntiClockWiseDirections(){
    // N
    // WE
    // S
    adjDirection['E']="NS";
    adjDirection['W']="NS";
    adjDirection['N']="EW";
    adjDirection['S']="WE";
    
    directions['E']={0,1};
    directions['W']={0,-1};
    directions['N']={-1,0};
    directions['S']={1,0};
    
    return ;
}

pair<ll,ll> findCellLocation(char targetChar){
    
    for(ll row=0;row<n;row++)
        for(ll col=0;col<m;col++)
            if(matrix[row][col]==targetChar)
                return {row,col};
    return {-1,-1};
}

ll getCharToIntDirection(char dir){
    if(dir=='E')
        return 0;
    if(dir=='W')
        return 1;
    if(dir=='N')
        return 2;
    return 3;
}

char getIntToCharDirection(ll dir){
    if(dir==0)
        return 'E';
    if(dir==1)
        return 'W';
    if(dir==2)
        return 'N';
    return 'S';
}

ll calculateLowestScoreToReachEnd(){
    pair<ll,ll> startLocation=findCellLocation('S');
    ll startX=startLocation.first,startY=startLocation.second;
    
    pair<ll,ll> endLocation=findCellLocation('E');
    ll endX=endLocation.first,endY=endLocation.second;
    
    vector<vector<ll>> dist(n,vector<ll>(m,LONG_MAX));
    //{dist, x, y, direction}
    priority_queue<vector<ll>,vector<vector<ll>>,greater<vector<ll>>> minHeap;
    minHeap.push({0,startX,startY,getCharToIntDirection('E')});
    dist[startX][startY]=0;
    while(!minHeap.empty()){
        vector<ll> curHeapEntry=minHeap.top();
        minHeap.pop();
        ll curDist=curHeapEntry[0],curX=curHeapEntry[1],curY=curHeapEntry[2],intDirection=curHeapEntry[3];
        char charDirection = getIntToCharDirection(intDirection);
        
        pair<ll,ll> curDirection=directions[charDirection];
        ll nextX=curX+curDirection.first,nextY=curY+curDirection.second;
        
        if(dist[curX][curY]+1 < dist[nextX][nextY] and matrix[nextX][nextY]!='#'){
            dist[nextX][nextY]=dist[curX][curY]+1;
            minHeap.push({dist[nextX][nextY],nextX,nextY,intDirection});
        }
        // clock wise direction
        pair<ll,ll> curDirection1=directions[adjDirection[charDirection][0]];
        nextX=curX+curDirection1.first,nextY=curY+curDirection1.second;
        
        if(dist[curX][curY]+1001 < dist[nextX][nextY] and matrix[nextX][nextY]!='#'){
            dist[nextX][nextY]=dist[curX][curY]+1001;
            minHeap.push({dist[nextX][nextY],nextX,nextY,getCharToIntDirection(adjDirection[charDirection][0])});
        }
        // anti clock wise direction
        pair<ll,ll> curDirection2=directions[adjDirection[charDirection][1]];
        nextX=curX+curDirection2.first,nextY=curY+curDirection2.second;
        
        if(dist[curX][curY]+1001 < dist[nextX][nextY] and matrix[nextX][nextY]!='#'){
            dist[nextX][nextY]=dist[curX][curY]+1001;
            minHeap.push({dist[nextX][nextY],nextX,nextY,getCharToIntDirection(adjDirection[charDirection][1])});
        }
        
    }
    
    return dist[endX][endY];
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
    populateClockWiseAndAntiClockWiseDirections();
    getInput();
    cout<<calculateLowestScoreToReachEnd();
    return 0;
}

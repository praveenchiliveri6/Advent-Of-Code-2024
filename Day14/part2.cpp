#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
ll width,height,cnt;
map<pair<ll,ll>,vector<pair<ll,ll>>> robotPositionMap;

void printMap(){
  vector<vector<char>> result(height+1,vector<char>(width+1,'.'));
  for(auto entry:robotPositionMap){
      pair<ll,ll> location=entry.first;
      ll x=location.first,y=location.second;
      result[x][y]='#';
  }
  for(ll row=1;row<=height;row++)
  {
      for(ll col=1;col<=width;col++)
          cout<<result[row][col];
      cout<<endl;
  }
  return ;
}

bool isPatternFound(){
  vector<vector<char>> result(height+1,vector<char>(width+1,'.'));
  for(auto entry:robotPositionMap){
      pair<ll,ll> location=entry.first;
      ll x=location.first,y=location.second;
      result[x][y]='#';
  }
  for(ll row=1;row<=height;row++)
  {
      for(ll col=1;col<=width;col++)
      if(result[row][col]=='#'){
        ll i=row,j=col,c1=0,c2=0,c3=0,c4=0;
        while(j<=width and result[i][j]=='#'){
          j++;
          c1++;
        }
        j--;
        while(i<=height and result[i][j]=='#'){
          i++;
          c2++;
        }
        i--;
        while(j>0 and result[i][j]=='#'){
          j--;
          c3++;
        }
        j++;
        while(i>0 and result[i][j]=='#'){
          i--;
          c4++;
        }
        
        i++;
        
        if(i==row and j==col and c1>5 and c2>5 and c3>5 and c4>5){
          return true;
        }
        
      }
  }
  
  return false;
  
}

void navigateRobotsForOneSecond(){
    map<pair<ll,ll>,vector<pair<ll,ll>>> nextRobotPositionMap;
    for(auto entry:robotPositionMap){
        pair<ll,ll> location=entry.first;
        vector<pair<ll,ll>> velocities=entry.second;
        ll x=location.first,y=location.second;
        for(auto velocity:velocities){
            ll v1=velocity.first,v2=velocity.second;
            ll nextX=(x+v1+width)%width;
            ll nextY=(y+v2+height)%height;
            
            if(nextX==0)
                nextX=width;
            if(nextY==0)
                nextY=height;
            nextRobotPositionMap[{nextX,nextY}].push_back({v1,v2});
        }
    }
    robotPositionMap=nextRobotPositionMap;
    cnt++;
    if(isPatternFound()){
      cout<<cnt<<endl;
      printMap();
    }
    return ;
}

ll calculateSafetyFactor(){
    ll widthMid=(width+1)/2;
    ll heightMid=(height+1)/2;
    ll q1=0,q2=0,q3=0,q4=0;
    for(auto entry:robotPositionMap){
        pair<ll,ll> location=entry.first;
        ll totalEntries=entry.second.size();
        ll x=location.first,y=location.second;
        if(x<widthMid){
            if(y<heightMid)
                q1+=totalEntries;
            else if(y>heightMid)
                q3+=totalEntries;
        }
        else if(x>widthMid){
            if(y<heightMid)
                q2+=totalEntries;
            else if(y>heightMid)
                q4+=totalEntries;
        }
    }
    
    return (q1*q2*q3*q4);
}

void navigateRobotsForXSeconds(ll seconds){
    for(ll second=7623;second<=seconds;second++){
        navigateRobotsForOneSecond();
    }
    
    return ;
}

vector<ll> parseInput(){
    ll n=inputLine.length();
    ll index=2;
    vector<ll> result;
    ll val=0;
    while(index<n and inputLine[index]!=',')
        val=val*10+(inputLine[index++]-'0');
    result.push_back(val);
    
    val=0;
    index++;
    while(index<n and inputLine[index]!=' ')
        val=val*10+(inputLine[index++]-'0');
    result.push_back(val);
    
    val=0;
    index+=3;
    bool isPositive=true;
    if(inputLine[index]=='-')
        isPositive=false,index++;
    
    while(index<n and inputLine[index]!=',')
        val=val*10+(inputLine[index++]-'0');
    if(!isPositive)
        val*=-1;
    result.push_back(val);
    index++;
    
    val=0;
    isPositive=true;
    if(inputLine[index]=='-')
        isPositive=false,index++;
    
    while(index<n)
        val=val*10+(inputLine[index++]-'0');
    if(!isPositive)
        val*=-1;
    result.push_back(val);
    
    return result;
}

void getInput(){
    width=101;
    height=103;
    while(!cin.eof()){
        getline(cin, inputLine);
        vector<ll> input=parseInput();
        ll x=input[0]+1,y=input[1]+1,v1=input[2],v2=input[3];
        robotPositionMap[{x,y}].push_back({v1,v2});
    }
    return ;
}

int main() {
    getInput();
    navigateRobotsForXSeconds(100000);
    //cout<<calculateSafetyFactor();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine1,inputLine2,inputLine3;
ll fewestTokens;
vector<ll> location1,location2,prizeLocation;

ll findSmallestNumOfTokensToWinPrize(ll limit){
    ll curTokens=LONG_MAX;
    // a1x+a2y=c1 
    // b1x+b2y=c2 
    
    // x = (c1-a2y)/a1 
    // b1 * (c1-a2y)/a1 + b2y=c2;
    /*
    (b1*c1)/a1 - (b1*a2)/a1 *y +b2y = c2;
    
   ( b2 - (b1*a2)/a1 ) y = c2 - (b1*c1)/a1;
   
    (b2*a1 - b1*a2) *y = (c2*a1-b1*c1)
    
    y = (c2*a1 - b1*c1)/(b2*a1 - b1*a2);
    */
    ll a1=location1[0],b1=location1[1];
    ll a2=location2[0],b2=location2[1];
    ll c1=prizeLocation[0],c2=prizeLocation[1];
    c1+=10000000000000;
    c2+=10000000000000;
    ll num=c2*a1-b1*c1;
    ll den=b2*a1-b1*a2;
    
    if(den==0 or num%den!=0)
        return 0;
    
    ll y=num/den;
    
    ll num1=c1-a2*y;
    if(num1%a1!=0)
        return 0;
        
    ll x=num1/a1;
    
    curTokens=3*x+y;
    
    return curTokens==LONG_MAX?0:curTokens;
}

vector<ll> parseInput(string s){
    ll n=s.length();
    ll index=0;
    vector<ll> location;
    while(index<n){
        ll num=0;
        while(index<n and isdigit(s[index])){
            num=num*10+(s[index++]-'0');
        }
        if(num>0){
            location.push_back(num);
        }
        index++;
    }
    return location;
}

void getInput(){
    string emptyLine;
    fewestTokens=0;
    while(!cin.eof()){
        getline(cin,inputLine1);
        getline(cin,inputLine2);
        getline(cin,inputLine3);
        if(!cin.eof()){
            getline(cin,emptyLine);
        }
        location1=parseInput(inputLine1);
        location2=parseInput(inputLine2);
        prizeLocation=parseInput(inputLine3);
        fewestTokens+=findSmallestNumOfTokensToWinPrize(100ll);
    }
    return ;
}

int main() {
    getInput();
    cout<<fewestTokens;
    return 0;
}

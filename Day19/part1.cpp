#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
set<string> availableTowelPatterns;
vector<string> queries;

bool isDesignPossible(string design){
    ll n=design.length();
    vector<ll> dp(n+1);
    dp[0]=1;
    for(ll index1=1;index1<=n;index1++){
        string curDesign;
        for(ll index2=index1;index2>0;index2--){
            curDesign=design[index2-1]+curDesign;
            if(availableTowelPatterns.find(curDesign)!=availableTowelPatterns.end())
                dp[index1]|=dp[index2-1];
        }
    }
    return dp[n];
}

ll countPossibleDesigns(){
    ll cnt=0;
    for(string design:queries){
        cnt+=isDesignPossible(design);
    }
    return cnt;
}

void parseInput(string s){
    ll n=s.length(),index=0;
    while(index<n){
        string curTowelPattern;
        while(index<n and s[index]!=','){
            curTowelPattern+=s[index++];
        }
        index+=2;
        availableTowelPatterns.insert(curTowelPattern);
    }
    return ;
}

void getInput(){
    getline(cin,inputLine);
    parseInput(inputLine);
    while(!cin.eof()){
        cin>>inputLine;
        queries.push_back(inputLine);
    }
    return ;
}

int main() {
    getInput();
    cout<<countPossibleDesigns();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long

string diskMap;
vector<ll> decodedDiskMap;
ll diskMapLength,checkSum;

void calculateCheckSum(){
    for(ll index=0;index<decodedDiskMap.size();index++){
        if(decodedDiskMap[index]==-1)
            break;
        checkSum+=index*decodedDiskMap[index];
    }
    
    return ;
}

void moveFilesFromEndToLeftMostFreeSpace(){
    ll startIndex=0,endIndex=decodedDiskMap.size()-1;
    while(startIndex<endIndex){
        while(startIndex<endIndex and decodedDiskMap[startIndex]!=-1)
            startIndex++;
        while(startIndex<endIndex and decodedDiskMap[endIndex]==-1)
            endIndex--;
        while(startIndex<endIndex and decodedDiskMap[startIndex]==-1 and decodedDiskMap[endIndex]!=-1)
            swap(decodedDiskMap[startIndex++],decodedDiskMap[endIndex--]);
    }
    
    return ;
}

void decodeDiskMap(){
    ll fileId=0;
    for(ll index=0;index<diskMapLength;index++){
        if(index%2==0){//file length
            for(ll rep=1;rep<=diskMap[index]-'0';rep++)
                decodedDiskMap.push_back(fileId);
            fileId++;
        }
        else{// free space
            for(ll rep=1;rep<=diskMap[index]-'0';rep++)
                decodedDiskMap.push_back(-1);
        }
    }
    return ;
}

void getInput(){
    cin>>diskMap;
    diskMapLength=diskMap.length();
    return ;
}

int main() {
    getInput();
    decodeDiskMap();
    moveFilesFromEndToLeftMostFreeSpace();
    calculateCheckSum();
    cout<<checkSum;
    return 0;
}

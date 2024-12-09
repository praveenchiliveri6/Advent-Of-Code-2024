#include <bits/stdc++.h>
using namespace std;
#define ll long long

string diskMap;
vector<ll> decodedDiskMap,fileLengthAndIndexVector;
ll diskMapLength,checkSum;
set<ll> freeSpaceIndexSet[10];


void calculateCheckSum(){
    for(ll index=0;index<decodedDiskMap.size();index++)
        if(decodedDiskMap[index]!=-1){
            checkSum+=index*decodedDiskMap[index];
        }
    
    return ;
}

pair<ll,ll> findTargetFreeSpaceIndexAndLength(ll fileSpace){
    ll freeSpaceIndex=LONG_MAX,freeSpaceLength=-1;
    for(ll reqFileSpace=fileSpace;reqFileSpace<10;reqFileSpace++)
        if(!freeSpaceIndexSet[reqFileSpace].empty() and *freeSpaceIndexSet[reqFileSpace].begin() < freeSpaceIndex){
            freeSpaceIndex = *freeSpaceIndexSet[reqFileSpace].begin();
            freeSpaceLength = reqFileSpace;
        }
    
    return {freeSpaceIndex, freeSpaceLength};
}

void moveFullFileFromEndToLeftMostFitFreeSpace(){
    ll diskMapIndex=diskMapLength-1,reducedDiskMapIndex=decodedDiskMap.size();
    if(diskMapLength%2==0){
        //last entry is free space;
        ll freeSpace=decodedDiskMap[diskMapIndex]-'0';
        reducedDiskMapIndex-=freeSpace;
        freeSpaceIndexSet[freeSpace].erase(reducedDiskMapIndex);
        diskMapIndex--;
    }
    
    for(;diskMapIndex>0;diskMapIndex-=2){
        ll fileSpace=diskMap[diskMapIndex]-'0';
        ll prevFreeSpace=(diskMapIndex-1>=0 ?(diskMap[diskMapIndex-1]-'0'):-1);
        reducedDiskMapIndex-=fileSpace;
        ll curFileIndex=reducedDiskMapIndex;
        ll curFileId=diskMapIndex/2;
        pair<ll,ll> targetSpot=findTargetFreeSpaceIndexAndLength(fileSpace);
        ll fittableFreeSpaceIndex=targetSpot.first;
        ll freeSpaceLength=targetSpot.second;
        
        if(fittableFreeSpaceIndex!=LONG_MAX){
            
            auto itr = freeSpaceIndexSet[freeSpaceLength].find(fittableFreeSpaceIndex);
            freeSpaceIndexSet[freeSpaceLength].erase(itr);
            
            for(ll rep=1;rep<=fileSpace;rep++)
                swap(decodedDiskMap[fittableFreeSpaceIndex++],decodedDiskMap[curFileIndex++]);
            
            if(freeSpaceLength > fileSpace){
                ll remSpace=freeSpaceLength-fileSpace;
                freeSpaceIndexSet[remSpace].insert(fittableFreeSpaceIndex);
            }
        }
        
        reducedDiskMapIndex-=prevFreeSpace;
        if(prevFreeSpace!=-1){
            ll inc=0;
            while(prevFreeSpace>0){
                auto itr = freeSpaceIndexSet[prevFreeSpace].find(reducedDiskMapIndex+inc);
                if(itr!=freeSpaceIndexSet[prevFreeSpace].end())
                    freeSpaceIndexSet[prevFreeSpace].erase(itr);
                prevFreeSpace--;
                inc++;
            }
            
        }
    }
    
    return ;
}

void decodeDiskMap(){
    ll fileId=0;
    for(ll index=0;index<diskMapLength;index++){
        if(index%2==0){//file length
            ll fileLength=diskMap[index]-'0';
            for(ll rep=1;rep<=fileLength;rep++)
                decodedDiskMap.push_back(fileId);
            fileId++;
        }
        else{// free space
            ll freeSpaceLength=diskMap[index]-'0';
            freeSpaceIndexSet[freeSpaceLength].insert(decodedDiskMap.size());
            for(ll rep=1;rep<=freeSpaceLength;rep++)
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
    moveFullFileFromEndToLeftMostFitFreeSpace();
    calculateCheckSum();
    cout<<checkSum;
    return 0;
}

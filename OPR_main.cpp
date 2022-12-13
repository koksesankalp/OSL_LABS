/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int finding_index(vector<int> page_reference, int sizeof_page_reference,vector<int> &frame,int frame_size,int index ){
    int farthest=index;
    int res;
    for(int i=0;i<frame_size;i++){
        res=-1;
        for(int j=index;j<sizeof_page_reference;j++){
            if(frame[i]==page_reference[j]){
                res=1;
                if(j>farthest){
                    farthest=j;
                    
                }
                break;
            }
            
        }
        if(res==-1){
            return i;
        }
        
    }
    return farthest;
}
void OPR(vector<int> page_reference, int sizeof_page_reference,vector<int> &frame,int frame_size ){
    unordered_map<int,int> Map;
    int page_fault=0;
    for(int i=0;i<sizeof_page_reference;i++){
        
        if(i<frame_size){
            frame[i]=page_reference[i];
            Map[page_reference[i]]++;
            page_fault++;
            continue;
            
        }
        
        if(Map.count(page_reference[i])){
            // page_fault++;
            continue;
        }
        else{
            int j=finding_index(page_reference,sizeof_page_reference,frame,frame_size,i+1);
            frame[j]=page_reference[i];
            Map[page_reference[i]]++;
            page_fault++;
        }
    }
    cout<<"Page Fault:-"<<page_fault;
}

int main()
{
    vector<int> page_reference;
    int sizeof_page_reference;
    cout<<"Enter size of page refrence:-";
    cin>>sizeof_page_reference;
    
    int a;
    cout<<"Enter page references:-";
    for(int i=0;i<sizeof_page_reference;i++){
        cin>>a;
        page_reference.push_back(a);
    }
    
    int frame_size;
    cout<<"Enter size of frame:-";
    cin>>frame_size;
    vector<int> frame(frame_size);
    
    OPR(page_reference,sizeof_page_reference,frame,frame_size);

    return 0;
}

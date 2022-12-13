/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int frame_size;
    cout<<"Enter frame size:- ";
    cin>>frame_size;
    cout<<endl;
    vector<int> Frame(frame_size);
    
    int no_of_pages;
    cout<<"Enter frame pages:- ";
    cin>>no_of_pages;
    cout<<endl;
    vector<int> Page;
    
    //7012030
    
    int a;
    for(int i=0;i<no_of_pages;i++){
        cout<<"Enter elemetn:- ";
        cin>>a;
        cout<<endl;
        Page.push_back(a);
    }
    
    
    
    unordered_map<int,int> Count_map;
    int page_fault=0;
    
    for(int i=0;i<no_of_pages;i++){
        if(i<frame_size){
            Frame.push_back(Page[i]);
            Count_map[Page[i]]=i;
            page_fault++;
            continue;
        }
        
        if(Count_map.count(Page[i])){
            cout<<"Count of "<<Page[i]<<":-"<<Count_map.count(Page[i])<<endl;
            Count_map[Page[i]]=i;
            continue;
        }
        else{
            cout<<"Entered else"<<i<<endl;
            page_fault++;
            int min=0;
            int key;
            for(auto itr=Count_map.begin();itr!=Count_map.end();++itr){
                if(min>itr->second){
                    key=itr->first;
                    min=itr->second;
                }
            }
            for(int j=0;j<Frame.size();j++){
                if(key==Frame[j]){
                    Frame[j]=Page[i];
                }
            }
            Count_map[Page[i]]=i;
            continue;
        }
            
        
        cout<<"index:- "<<i<<endl;
        
    }
    cout<<"Page Fault:- "<<page_fault;

    return 0;
}




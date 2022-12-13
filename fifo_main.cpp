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
    queue<int> frame;
    int frame_size;
    cout<<"Enter frame size"<<endl;
    cin>>frame_size;
    vector<int> page_no;
    unordered_map<int,int> Map;
    int n;
    cout<<"Frame size:- "<<frame.size();
    cout<<"Entering number of pages"<<endl;
    cin>>n;
    int a;
    //  1, 3, 0, 3, 5, 6, 3 
    cout<<"enter elements"<<endl;
    for(int i=0;i<n;i++){
        cin>>a;
        page_no.push_back(a);
    }
    cout<<"vector size"<<page_no.size()<<endl;
    int j=0;
    int page_fault=0;
    
    while(j!=page_no.size()){
        cout<<"entered in loop"<<j<<endl;
        if(frame.size()==frame_size){
            if(Map.count(page_no[j])){
                j++;
                continue;
            }
            
            else{
                Map.erase(frame.front());
                frame.pop();
                cout<<"Frame size :- "<<frame.size()<<endl;
            }
            
            
        }
        
        frame.push(page_no[j]);
        Map[page_no[j]]++;
        page_fault++;
        j++;
        cout<<"j:-"<<j<<endl;
    }
    cout<<"Page fault:- "<<page_fault;
    
}




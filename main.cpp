#include <iostream>
#include <stdlib.h>
#include  <bits/stdc++.h>
#include <fstream>
#include<sstream>//use for conversion of string to number
using namespace std;

ofstream output_file;

// getting data
void get_data(string curr_inst,string data,char** external_memory,char **cpu){
    string end_str="";
    end_str=curr_inst.substr(2,2);
    stringstream ss;
    ss<<end_str;
    int num;
    ss>>num;
    
    // IR status
    for(int i=0;i<4;i++){
        cpu[1][i]=curr_inst[i];
    }
    
    cout<<"Data at virtual memory ";
    for(int i=num, k=0;i<=num+9;i++){
        for(int j=0;j<4;j++,k++){
            external_memory[i][j]=data[k];
            cout<<external_memory[i][j]<<" ";
        }
        
    }
    cout<<endl;
    return;
    
}



// loading data
void load_data(string curr_inst,char** external_memory,char **cpu){
    string end_str="";
    end_str=curr_inst.substr(2,2);
    stringstream ss;
    ss<<end_str;
    int num;
    ss>>num;
    
    // IR status
    for(int i=0;i<4;i++){
        cpu[1][i]=curr_inst[i];
    }
    
    // loading data to R 
    cout<<"Data at R";
    for(int i=0;i<4;i++){
        cpu[0][i]=external_memory[num][i];
    }
    cout<<endl;
    return ;
}



// SR
void cpu_to_em(string curr_inst,char** external_memory,char **cpu){
    string end_str="";
    end_str=curr_inst.substr(2,2);
    stringstream ss;
    ss<<end_str;
    int num;
    ss>>num;
    
    
    cout<<"Data at vm from R ";
    for(int i=0;i<4;i++){
        external_memory[num][i]=cpu[0][i];
        cout<<external_memory[num][i]<<" ";
    }
    cout<<endl;
    // IR status
    for(int i=0;i<4;i++){
        cpu[1][i]=curr_inst[i];
    }
    return ;
}



// putting data
void put_data(string curr_inst,char** external_memory,char** cpu,string data){
    string end_str="";
    end_str=curr_inst.substr(2,2);
    stringstream ss;
    ss<<end_str;
    int num;
    ss>>num;
    
    output_file.open("Output_File.txt");
    if( !output_file ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
    
    for(int i=num;i<data.size();i++){
        for(int j =0;j<4;j++){
            output_file<<external_memory[i][j];
        }
        
    }
    
    
    // IR status
    for(int i=0;i<4;i++){
        cpu[1][i]=curr_inst[i];
    }
    
    return ;
    
}


// Comparison
bool compare(string curr_inst,char** external_memory,char **cpu){
    string end_str="";
    end_str=curr_inst.substr(2,2);
    stringstream ss;
    ss<<end_str;
    int num;
    ss>>num;
    
    for(int i=0;i<4;i++){
        if(cpu[0][i]!=external_memory[num][i]){
            
            return false;
        }
    }
    
    // IR status
    for(int i=0;i<4;i++){
        cpu[1][i]=curr_inst[i];
    }
    
    return true;
}


// BT INST.
void branch(string curr_inst,char** external_memory,char** cpu ){
    string end_str="";
    end_str=curr_inst.substr(2,2);
    stringstream ss;
    ss<<end_str;
    int num;
    ss>>num;
    
    if(cpu[3][0]=='T'){
        cpu[2][0]=end_str[0];
        cpu[2][1]=end_str[1];
        
    }
    
    // IR status
    for(int i=0;i<4;i++){
        cpu[1][i]=curr_inst[i];
    }
    
    return ;
    
}

void halt(){
    exit(1) ;
}










// MAIN()

int main()
{
    // Main memory creation
    char** external_memory=new char*[100];
    for(int i=0;i<100;i++){
        external_memory[i]= new char[4];
    }
    for(int i=0;i<100;i++){
        for(int j =0; j<4; j++){
            external_memory[i][j]= '\0';
        }
    }
    
    
    // cpu creation
    char **cpu=new char* [4];
    for(int i=0;i<2;i++){
        cpu[i]= new char[4];
    }
    cpu[2]=new char[2];
    cpu[3]=new char[1];
    
    // creating and checking file is open or not
    ifstream in("INPUT_FILE.txt") ;
    
    // for read operation
    
    string temp="";
    
    string input="";
    string data="";
    
    
    while(getline(in,temp)){
        if(temp[0]=='$'&&temp[1]=='D'){
            break;
        }
        // getline(file,temp);
        
        
        if(temp[0]=='$'&&temp[1]=='A'){
            continue;
        }
        input=temp;
    }
    cout<<endl;
    cout<<"Instruction:- "<<input;
    cout<<endl;
    while(getline(in,temp)&&(temp[0]!='$'&&temp[1]!='E')){
        // getline(file,temp);
        if(temp[0]=='$'&&temp[1]=='A'){
            continue;
        }
        data=temp;
    }
    cout<<"data:-"<<data;
    cout<<endl;
    
    
    
    // loading to external memory
    int k=0;
    cout<<"external memory"<<endl;
    for(int i=0;i<=input.size()/4;i++){
        for(int j=0;j<4;j++,k++){
            external_memory[i][j]= input[k];
            cout<<external_memory[i][j]<<" ";
        }
        cout<<endl;
    }
    
    for(int i=0;i<=input.size()/4;i++){
        string append="";
        for(int j=0;j<4;j++,k++){
            append+=external_memory[i][j];
        }
        cout<<append<<endl;
        string str=append.substr(0,2);
        if(str=="GD"){
            get_data(append,data,external_memory,cpu);
        }
        else if(str=="LR"){
            load_data(append,external_memory,cpu);
        }
        else if(str=="PD"){
            put_data(append,external_memory,cpu,data);
        }
        else if(str=="SR"){
            cpu_to_em(append,external_memory,cpu);
        }
        else if(str=="CR"){
            if(compare(append,external_memory,cpu)){
                cpu[3][0]='T';
            }
            else{
                cpu[3][0]='F';
            }
        }
        else if(str=="BT"){
            branch(append,external_memory,cpu);
        }
        else{
            halt();
        }
        
    }

    return 0;
}

// INPUT TEXT


// $AMJ000200010001
// GD10LR12SR15PD10H
// $DTA
// I LIKE THIS PEN OF 
// $END0002
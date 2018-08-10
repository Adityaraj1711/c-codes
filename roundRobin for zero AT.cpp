#include<iostream>
using namespace std;

bool check(int a[4][4]){
        for(int  i =0;i<4;i++){
                if(a[i][2]!=0)
                        return false;
        }
        return true;
}


int main(){
        int q , sumb = 0;
        cout<<"enter quanta";
        cin>>q;
        int a[4][4];
        for(int i = 0;i<4;i++){
                a[i][0]=i+1;
                cout<<"\n Enter arrival time : ";
                cin>>a[i][1];
                cout<<"\n Enter burst time   : ";
                cin>>a[i][2];
        }
        int stack[100][2];
        bool br = true;
        int z = 0;
        while(br){
                for(int i =0;i<4;i++){
                        if(a[i][2]>0){
                                stack[z][0] = a[i][0];
                                if(a[i][2]>=q){ 
                                        a[i][2]-=q;
                                        stack[z][1] = q;
                                        z++;
                                }
                                else{
                                        stack[z][1] = a[i][2];
                                        a[i][2]=0;
                                        z++;
                                }
                                
                        }
                        if(check(a)){
                                br = false;
                        }
                }
        }
        int time = 0;
        for(int i =0;i<z;i++){
                cout<<"\nprocess id: "<<stack[i][0]<<" for time: "<<stack[i][1]+time;                
                time+=stack[i][1];
        }
        return 0;
}

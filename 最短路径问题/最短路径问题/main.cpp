//
//  main.cpp
//  最短路径问题
//
//  Created by 张旭伟 on 06/12/2016.
//  Copyright © 2016 Inno. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream fin("in.txt");
#define maxLength 20

int matrix[maxLength][maxLength];   //有向图的邻接表
int minPath[maxLength];             //存储这每个节点到终点的最短路径
int trace[maxLength];               //记录下最短线路
string Node[maxLength] = {"A","B1","B2","C1","C2","C3","C4","D1","D2","D3","E"};//节点标记
int v_n; //节点个数

int MinDistance(int v);

int main()
{
    fin>>v_n;
    for(int i=0;i<v_n;i++)
    {
        for(int j=0;j<v_n;j++)
        {
            fin>>matrix[i][j];
            cout<<matrix[i][j]<<"-";
        }
        cout<<endl;
    }
    memset(minPath,0,sizeof(int)*maxLength);
    memset(trace,0,sizeof(int)*maxLength);
    
    int minD = MinDistance(0);
    cout<<"最短路径："<<minD<<endl;
    int k=0;
    cout<<Node[0]<<"-->";
    while(minD>0)
    {
        cout<<Node[trace[k]]<<"-->";
        minD = minD-matrix[k][trace[k]];
        k = trace[k];
    }
    cout<<endl;
    return 0;
}

int MinDistance(int v)
{
    if(minPath[v]>0) return minPath[v];
    if(v==v_n-1) return 0;     //边界值
    int min=1000,t,j;
    for(int i=v+1;i<v_n;i++)
    {
        if(matrix[v][i]>0)
        {
            t = matrix[v][i]+MinDistance(i);
            if(min>t){ min=t; j=i;}
        }
    }
    minPath[v]=min;
    trace[v]=j;
    return minPath[v];
}

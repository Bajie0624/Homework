//
//  main.cpp
//  dijkstra算法
//
//  Created by 张旭伟 on 08/12/2016.
//  Copyright © 2016 Inno. All rights reserved.
//

#include <iostream>
#include <stdlib.h>

using namespace std;

int dijkstra(int (*graphy)[8], int vertexs, int s_v, int e_v, int *path);

int main()
{
    int g[8][8];
    memset(g, -1, sizeof(int)*8*8);
    g[0][0] = 0, g[1][1] = 0, g[2][2] = 0, g[3][3] = 0;
    g[4][4] = 0, g[5][5] = 0, g[6][6] = 0,
    g[1][2] = 15, g[1][4] = 12;
    g[1][3] = 2, g[2][5] = 6;
    g[3][5] = 8, g[3][6] = 4;
    g[4][7] = 3, g[5][7] = 9;
    g[6][4] = 5, g[6][7] = 10;
    g[7][2] = 4;
    
    int p[8];
    int s = 1;
    int e;
    int path;
    for(e=1; e<8; e++)
    {
        path = dijkstra(g, 8, s, e, p);
        if(path != -1)
        {
            cout<<"shortest path, from "<<s<<" to "<<e<<" is: "<<path<<endl;
            cout<<"path: ";
            for(int i=e; p[i] != -1; i=p[i])
                cout<<i<<"<--";
            cout<<s<<endl<<endl;
        }
        else
            cout<<"shortest path, from "<<s<<" to "<<e<<" is not exist."<<endl<<endl;
    }
    
    return 0;
}


//构建dijkstra算法
int dijkstra(int (*graphy)[8], int vertexs, int s_v, int e_v, int *path)
{
    int *dist; //最短路径
    int *vis;  //已访问过的顶点
    int num;
    int min, k;
    
    dist = new int[vertexs];
    vis = new int [vertexs];
    
    //初始化，-1代表max_value
    memset(dist, -1, sizeof(int)*vertexs);
    //起点到终点最短距离为0
    dist[s_v] = 0;
    memset(vis, 0, sizeof(int)*vertexs);
    memset(path, -1, sizeof(int)*vertexs);
    num = vertexs-1;
    while(num)
    {
        //贪心策略：从访问过的顶点中，找出最短路径，从已知的最短路径开始延伸
        min = -1;
        k = -1;
        for(int i=0; i<vertexs; i++)
        {
            if(vis[i] != 1 && dist[i] != -1 &&
               (min != -1 && dist[i] < min || min == -1))
            {
                min = dist[i];
                k = i;
            }
        }
        
        //终点最短路径已找到或所有顶点最短路径都已找到
        if(e_v == k || min == -1)
            break;
        //标记访问过的顶点
        vis[k] = 1;
        num--;
        
        
        //更新未访问过邻接顶点的最短路径
        for(int i=0; i<vertexs; i++)
        {
            if(vis[i] != 1 && graphy[k][i] != -1 &&
               (dist[i] != -1 && dist[i] > min + graphy[k][i] || dist[i] == -1))
            {
                dist[i] = min + graphy[k][i];
                path[i] = k; //更新记录前驱顶点，为下一步寻找提供路径
            }
        }
    }
    min = dist[e_v];
    delete [] dist;
    delete [] vis;
    return min;
}

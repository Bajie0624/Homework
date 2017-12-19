//
//  main.cpp
//  霍夫曼编码——数据结构
//
//  Created by 张旭伟 on 25/11/2016.
//  Copyright © 2016 Inno. All rights reserved.
//

#include <iostream>
using namespace std;
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define BUFFERSIZE 6000
#define VERBAL 0
#define DEBUG 1
#define MAXVALUE 6000
#define base_url "./"

typedef struct node{
  int weight;
  int lchild,rchild,parent;
}THNode, * TpHTree;

typedef struct huffman_code {
    int weight;
    char * pcode;
}THCode, *TpHcodeTab;

void select_subtree(TpHTree huffman,int n,int *subA,int *subB){
    int i,suba=-1,subb=-1,a=MAXVALUE,b=MAXVALUE;
for(i=0;i<=n; i++){
if(huffman[i].parent == -1)
{
    if(huffman[i].weight<a)
    {
        a=huffman[i].weight;
        subb=suba;
        suba=i;
    }
    else if(huffman[i].weight<b)
    {
        b=huffman[i].weight;
        subb=i;
    }
}
}
    *subA=suba;
    *subB=subb;
    return ;
}
//构建霍夫曼树，指明权重
TpHTree create_huffman_tree(int weights[],int n){
    TpHTree pht;
    int subA,subB,i,num=(2*n)-1;
    pht=(TpHTree)malloc(sizeof(THNode)*num);
    for(i=0;i<num;i++){
        pht[i].weight=weights[i];
        pht[i].lchild=-1;
        pht[i].rchild=-1;
        pht[i].parent=-1;
    }
    for(i=n;i<num;i++){
        select_subtree(pht, i-1, &subA, &subB);
        pht[subA].parent=i;
        pht[subB].parent=i;
        pht[i].lchild=subA;
        pht[i].rchild=subB;
        pht[i].weight=pht[subA].weight+pht[subB].weight;
    }
    return pht;
}

//输出霍夫曼树
void output_huffman_tree(TpHTree pht,int n){
    int i;
    for(i=n+1;i<=2*n-1;i++){
        cout<<pht[pht[i].lchild].weight;
        cout<<pht[i].weight;
        cout<<pht[pht[i].rchild].weight<<endl;
        
    }
        
}
TpHcodeTab build_huffman_code_table(TpHTree pht,int n){
    int i,j,k,m,len;
    TpHcodeTab table=(TpHcodeTab)malloc(sizeof(THCode)*n);
    char *pch=(char*)malloc(n+1);
    for (i=0; i<n; i++) {
        m=n;
        j=i;
        k=pht[j].parent;
        table[i].weight=pht[i].weight;
        while (k!=-1) {
            if (pht[k].lchild==j) {
                pch[m--]='0';
            }else
                pch[m--]='1';
            j=k;
            k=pht[j].parent;
        }
        len=n-m+1;
        table[i].pcode=(char*)malloc(len);
        strncpy(table[i].pcode, &pch[m], strlen(&pch[m]));
    }
    return table;
}
char *encode_huffman(TpHcodeTab pht,char *msg,char*dict,int n){
    int i,j;
    long m,len,offset=0;
    char *pch;
    pch=(char*)malloc(BUFFERSIZE+1);
    m=strlen(msg);
    for(i=0;i<m;i++){
        for (j=1;j<=n;j++) {
            if(msg[i]==dict[j]){
                len=strlen(pht[j].pcode);
                strncpy(&pch[offset], pht[j].pcode,len);
                offset+=len;
                break;
            }
        }
    }
    return pch;
}
char *decode_huffman(TpHTree pht,char *msg,char *dict,int n){
    int i,pos=0,idx=0;
    long len;
    char *pch;
    pch=(char*)malloc(BUFFERSIZE+1);
    len=strlen(msg);
    for(i=0;i<len;){
        idx=(2*n)-2;
        while (idx>=n) {
            if(msg[i]=='0'){
                idx=pht[idx].lchild;
                i++;
            }else{
                idx=pht[idx].rchild;
                i++;
            }
        }
        pch[pos]=dict[idx];
        pos++;
    }
    return pch;
}

void destroy_hctable(TpHcodeTab hcode_table,int n){
    int i;
    for (i=0;i<n;i++)
        if(hcode_table[i].pcode)
            free(hcode_table[i].pcode);
    free(hcode_table);
}


long  openFile(char *fileName,char *message){
    long slen;
    char name[100];
    
    sprintf(name, "%s%s","",fileName);
    FILE *fp=fopen(name, "r");
    if(!fp){
        cout<<"You are wrong!"<<endl;
        exit(0);
    }else{
        cout<<"开始";
        
    }
    memset(message, 0, BUFFERSIZE);
    if(fgets(message,BUFFERSIZE-1,fp)==NULL){
        cout<<"fgets error"<<endl;
        exit(0);
    }
    else{
        cout<<message;
    }
    slen=strlen(message);
    fclose(fp);
    cout<<"成功读取文件,文件内容为："<<endl;
    return slen;
}

//统计出现的字符频率
int calc_freq(char text[],int **freq,char **dict,long n){
    int i,k,nchar=0;
    int *pwght;
    char *pch;
    int tokens[128]={0};
    for(i=0;i<n;i++){
        tokens[text[i]]++;
    }
    for (i=1; i<128; i++) {
        if (tokens[i]) {
            nchar++;
        }
    }
    pwght=(int *)malloc(sizeof(int*)*nchar);
    if(!pwght){
        cout<<"为权重数组分配空间失败"<<endl;
        exit(0);
    }
    pch=(char *)malloc(nchar);
    if(!pch){
        cout<<"为字符数组分配空间失败"<<endl;
        exit(0);
    }
    k=0;
    for (i=0; i<128; i++) {
        if(tokens[i]>0){
            pwght[k]=tokens[i];
            pch[k]=(char)i;
            k++;
        }
    }
    *freq=pwght;
    *dict=pch;
    return nchar;
}


int main(int argc, char *argv[])
{
    int i,nleaves=0;
    long nmsg;
    char fileName[100]="/Users/zhangxuwei/Desktop/huffman.txt";
    TpHTree pht=NULL;
    TpHcodeTab hcode_table;
    char msg[BUFFERSIZE];
    int *weights=NULL;
    char *dict=NULL;
    char *pcode = NULL;
    char*ptxt=NULL;
    nmsg = openFile(fileName, msg);
    cout<<msg;
    nleaves=calc_freq(msg,&weights,&dict,nmsg);
    
for(i=0;i<nleaves;i++){
    
        cout<<i<<dict[i]<<weights[i]<<endl;
}
    pht=create_huffman_tree(weights,nleaves);
    output_huffman_tree(pht,nleaves);
    hcode_table=build_huffman_code_table(pht,nleaves);
    cout<<"Huffman编码表如下: "<<endl;
    pcode=encode_huffman(hcode_table,msg,dict,nleaves);
    cout<<"Huffman编码为："<<pcode<<endl;
    
    ptxt=decode_huffman(pht,pcode,dict,nleaves);
    cout<<"编码的解码为："<<ptxt<<endl;
    destroy_hctable(hcode_table,nleaves);
    
    if(pht){
        free(pht);
        }
    if(pcode){
        free(pcode);
    }
    if(ptxt){
        free(ptxt);
        }
    if(dict){
        free(dict);
    }
    if(weights){
        free(weights);
    }

    return 0;
}

//
//  main.cpp
//  约瑟夫问题
//
//  Created by 张旭伟 on 04/11/2016.
//  Copyright © 2016 Inno. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;
struct ListNode{  //链表节点
    ListNode(int pos){
        this->pos=pos;
        next=NULL;
    }
    int pos;
    ListNode* next;
};
struct List{ // 创建循环链表
    ListNode* head;
    List(){
        head=new ListNode(-1);
        head->next=head;
    }
    void add_p(int p){   // 加入p
        if(head->pos!=-1)
        {
            ListNode* temp=new ListNode(p);
            temp->next=head->next;
            head->next=temp;
        }
        else{
            head->pos=p;
        }
    }
    void pop(ListNode* p){  //删除p->next
        ListNode* temp=p->next;
        p->next=temp->next;
        delete temp;
    }
};
List* createList(int n);
void playGame(List* stuList,int tot,int m);

int main(){
    cout<<"请输入：n m"<<endl;
    int n,m;
    cin>>n>>m;
    List* stuList=createList(n);
    playGame(stuList,n,m);
    return 0;
}
List* createList(int n){
    List* temp=new List();
    temp->add_p(1);
    for(int i=n;i>1;i--){
        temp->add_p(i);
    }
    return temp;
}
void playGame(List* stuList,int tot,int m){//针对第一种情况即m为0时
    if(m==0){
        cout<<"出局顺序: "<<endl;
        for(int i=1;i<tot;i++){
            cout<<i<<" ";
        }
        cout<<"The win: "<<tot<<endl;
        return ;
    }else{
    ListNode* current=stuList->head;
    cout<<"出局顺序: "<<endl;
    for(int i=1;i<tot;i++){ // 玩top-1局游戏
        for(int j=1;j<m;j++){ // 每次传递m-1次
            current=current->next;
        }
        cout<<current->next->pos<<" ";  //出局者的编号
        stuList->pop(current); //出局第m次拿到的人
        current=current->next;// 传递到胜利者
    }
    cout<<"The win: "<<current->pos<<endl;
}
}





                
                
                

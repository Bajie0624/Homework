//
//  main.cpp
//  FridayLast1
//
//  Created by 张旭伟 on 11/12/2017.
//  Copyright © 2017 Inno. All rights reserved.
//

//有以下数字：11,12,13,2,3,4,5,6,7,16,17,18.
//将以上数据依次压入容器deque中，选用一种排序算法排序后，连续弹出3个数据（pop_front后,对剩余数据进行累加并输出；而后删除所有大于11的数，并输出。
#include <deque>
#include <map>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

class DoSum{
    int sum;
        public :
            void operator() (int elem){
                elem = sum + elem;//计算累加和
                sum  = elem;
            }
            operator int(){
                return sum;
            }
};

bool IsTrueRange(int num){
    return (num > 11);
}

int main(){
    int data[] = {11,12,13,2,3,4,5,6,7,16,17,18};//原始数据
    int time = 3;//弹出数据个数
    deque<int>deq;
    deque<int>deq2;
    //把数据加入到容器
    for(int i = 0;i<12;i++)
        deq.push_back(data[i]);
    //输出原始数据
    cout<<"原始的数据：";
    copy(deq.begin(),deq.end(),ostream_iterator<int >(cout," "));
    cout<<endl;
    //选用快排进行排序，从大到小,可以增加难度换成冒泡排序等其他排序方式，时间如果足够，可以选择换个排序算法
    sort(deq.begin(),deq.end(),greater<int >());
    //输出排序后的序列
    cout<<"快速排序后的顺序: ";
    copy(deq.begin(),deq.end(),ostream_iterator<int >(cout," "));
    cout<<endl;
    //连续弹出time个数据
    while(time--)
        deq.pop_front();
    //输出弹出数据后的序列
    cout<<"弹出后的序列: ";
    copy(deq.begin(),deq.end(),ostream_iterator<int >(cout," "));
    cout<<endl;
    //计算序列的累加和  (使用accumulate())
    cout<<"累加和: ";
    cout<<accumulate(deq.begin(),deq.end(),0)<<endl;
    //删除大于11的值，和上面的弹出方法类似
    remove_copy_if(deq.begin(), deq.end(), back_inserter(deq2), IsTrueRange);
    cout<<"删除所有大于11的数后的输出结果: ";
    copy(deq2.begin(), deq2.end(), ostream_iterator<int>(cout," "));
    cout<<endl;
    return 0;
}

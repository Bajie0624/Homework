//
//  main.cpp
//  FridayLast1
//
//  Created by 张旭伟 on 11/12/2017.
//  Copyright © 2017 Inno. All rights reserved.
//


//有以下数字：11,12,13,2,3,4,5,6,7,16,17,18.将其装入vector容器中，
//采用仿函数和输出迭代器分别输出所有的偶数和奇数，接着输出大于等于7且小于17的所有数到一个list容器中，
//最后将list容器内容进行输出。

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>
#include <iterator>
using namespace std;

//判断是否为偶数
class IsEven{
public:
    void operator()(int i)
    {
        if (i % 2 == 0){
            cout << i<< " ";
    }
    }
};
//判断是否是奇数
class IsOdd{
public:
    void operator()(int i){
        if (i % 2 != 0) {
            cout<< i <<" ";
        }
    }
};
//大于等于7且小于17
bool IsTrueRange(int num)
{
    return ( !(num >=7 && num < 17));
}
int main(int argc, char *argv[])
{
    int data[] = {11,12,13,2,3,4,5,6,7,17,18};
    vector<int> vec;
    list<int> lit;
    size_t len;
    len = sizeof(data)/sizeof(data[0]);
    vec.insert(vec.begin(), data, data+len);
    //输出偶数
    cout<<"偶数：";
    for_each(vec.begin(), vec.end(), IsEven());
    cout << endl;
    //输出奇数
    cout<<"奇数：";
    for_each(vec.begin(), vec.end(), IsOdd());
    cout << endl;
    //大于等于7且小于17的数
    remove_copy_if(data, data+len, back_inserter(lit), IsTrueRange);
    cout<<"大于等于7且小于17的数：";
    copy(lit.begin(), lit.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}

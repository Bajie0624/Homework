//
//  main.cpp
//  FridayLast2
//
//  Created by 张旭伟 on 11/12/2017.
//  Copyright © 2017 Inno. All rights reserved.
//

//有学生信息5个(姓名，学号)：{张三,2011123}, {王二,2011235},{刘七,2012009},{唐六,2012676},{堂八,2010527}.将姓名作为key，学号作为value,采用map容器进行装载，而后统计2011,2012,2010级学生个数并输出，最后可分别输入姓名和学号后对容器进行信息查询（既可以用学号，也可以用姓名对容器进行查询）。

#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
//仿函数定义
class FindSame{
private:
    int num;//年级人数
    string str1;//年级
    string str2;//学号
    public ://构造函数
    FindSame(string s):str1(s),num(0){
    }
    //计算年级人数
    void operator()(pair<string,string> elem){
        str2 = elem.second;
        //寻找序号特点，只比较第2和第3位是否相等
        if(str2[2] == str1[2] && str2[3] == str1[3])
            num++;
    }
    //返回人数
    operator int(){
        return num;
    }
};

int main(){
    //定义容器
    map<string,string> Info;
    map<string,string>::iterator Info1;
    int count = 0;//年级人数计数器
    string in; //查找字符串，姓名或学号
    //容器的内容
    Info.insert(make_pair("张三","2011123"));
    Info.insert(make_pair("王二","2011235"));
    Info.insert(make_pair("刘七","2012009"));
    Info.insert(make_pair("唐六","2012676"));
    Info.insert(make_pair("堂八","2010527"));
    //计算不同年级的人数
    count = for_each(Info.begin(),Info.end(),FindSame("2010"));
    cout<<"2010 : "<<count<<endl;
    count = for_each(Info.begin(),Info.end(),FindSame("2011"));
    cout<<"2011 : "<<count<<endl;
    count = for_each(Info.begin(),Info.end(),FindSame("2012"));
    cout<<"2012 : "<<count<<endl;
    //输入查找信息（姓名或者学号）
    cout<<"请输入要查找信息（姓名或者学号）:"<<endl;
    cin>>in;
    cout<<"name "<<" number"<<endl;
    for(Info1 = Info.begin();Info1 != Info.end();++Info1){
        if(Info1->first == in || Info1->second ==in){
            cout<<Info1->first <<"   "<<Info1->second<<endl;
            break;
        }
    }
    //无法找到信息
    if(Info1 == Info.end())cout<<"not exist"<<endl;
    getchar();
    return 0;
}

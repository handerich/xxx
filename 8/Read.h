#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

#define File_node "design.node"
#define File_are  "design.are"
#define File_clk  "design.clk"
#define File_net  "design.net"

//TDM结构体
struct TDM
{
    string m_Name;
    double m_Data = 0;
};
//时钟结构体
struct CLK
{
    string m_Name;
    float m_Data = 0;
};

//TDM_delay()--计算TDM延时
double TDM_delay(string name, double r);
//Read()--读取文件，获取相应信息并存存储
void Read();
//Print_nodeArr()--打印nodeArr内容
void Print_nodeArr();
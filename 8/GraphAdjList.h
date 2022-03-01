#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define Tsu 1.f;
#define Tco 1.f;
#define Thd 1.f;
#define Tcomb 0.1;

//边结构体
struct ArcNode
{
    size_t srcVex; //上一顶点所在下标
    size_t adjVex; //邻接顶点所在表中下标
    double weight; //权重
    ArcNode* next; //依附同一顶点的下一条边
    ArcNode* front_next = NULL; //指向同一顶点的下一条边
};
//结点结构体
struct VexNode
{
    string m_Name; //顶点名
    string m_FPGA; //顶点所属的FPGA
    ArcNode* first = NULL; //指向依附该顶点的第一条边的指针
    string m_Ff;  //ff信息
    string m_Clk_Name; 
    double m_Clk_Data = 0;  //Clk信息
    double Tcycle = 0; //时钟周期
    double m_Clk_Delay = 0;
    double m_fixed_delay = 0;   //实时更新  固定延时
    double m_wire_delay = 0;   //实时更新  线延时
    double Tdp;   //实时更新  中间结果
    ArcNode* front = NULL; //指向该顶点的第一条边的指针（追溯）
};
//路径信息
struct Paths
{
    vector<ArcNode*> Path_Node;
};
//边数据
struct ArcData
{
    string Tail; //弧尾
    string Head; //弧头 （箭头）
    double Weight;  //权重（延时）
};
class GraphAdjList
{ 
//建立图
public:
    GraphAdjList();		//构造函数：初始化图种类		
    ~GraphAdjList();	//析构函数
    
     //创建有向网
    void _CreateDN(vector<ArcData>& arcsList);
    //定位顶点元素位置
    size_t _Locate(string vertex);
    //插入边							
    void _InsertArc(int tail, int head, double weight);
    //显示 图
    void Display();

//遍历路径
public:
    //将节点进行分类
    void Classify_node();
    //遍历所有路径
    void DFS_All_Path();
private:
    vector<size_t> vexs_head;  //输入节点数组
    size_t headNum = 0;   //输入节点数
    vector<size_t> vexs_tail;  //输出节点数组
    size_t tailNum = 0;   //输出节点数
    vector<size_t> vexs_ff;  //寄存器节点数组
    size_t ffNum = 0;   //寄存器节点数
    vector<size_t> vexs_clk;  //clk节点数组
    size_t clkNum = 0;   //clk节点数

    vector<int> vexs_visited; //节点访问数组

    Paths Path;   //路径结构体
    vector<Paths> Path_ff_ff;    //ff->ff
    vector<Paths> Path_ff_out;    //ff->out
    vector<Paths> Path_in_ff;    //in->ff
    vector<Paths> Path_in_out;    //in->out
    vector<Paths> Path_clk_ff;  //clk->ff

    //深度优先遍历 非递归									
    void _DFS(int index1, int index2,int path_choice);

//计算
public:
    //Calc_path()--计算路径
    void Calc_path();
    //打印路径信息
    void Print_path();
};

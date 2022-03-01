#include "GraphAdjList.h"
using namespace std;

extern vector<VexNode> nodeArr;

/*****************************************建立图*****************************************/
//GraphAdjList()--构造函数：初始化图类型
GraphAdjList::GraphAdjList() {}
//~GraphAdjList()--析构函数：销毁图
GraphAdjList::~GraphAdjList() {}

//_CreateDN()--创建有向网,邻接矩阵为非对称矩阵
void GraphAdjList::_CreateDN(vector<ArcData>& arcsList)
{
	//初始化 Tail Head 顶点下标索引
	int tail = 0, head = 0;
	//遍历边数据列表
	for (size_t i = 0; i < arcsList.size(); i++)
	{
		//按序获取边（弧）
		//定位（或设置）边的两端顶点位置
		tail = _Locate(arcsList[i].Tail);
		head = _Locate(arcsList[i].Head);
		//插入边   箭头端为弧头，另一端为弧尾
		_InsertArc(tail, head, arcsList[i].Weight);
	}
}
//_Locate()--定位顶点元素位置
size_t GraphAdjList::_Locate(string vertex)
{
	//后期可改成【字典树】，顶点数超过100个后定位顶点位置可更快

	//遍历定位顶点位置
	for (size_t i = 0; i < nodeArr.size(); i++)
	{
		if (vertex == nodeArr[i].m_Name)
		{
			return i;
		}
	}
	return -1;
}
//_InsertArc()--插入边（元操作，不分有向/无向）
void GraphAdjList::_InsertArc(int tail, int head, double weight)
{
	size_t arcNum = 0;
	//边结点指针：初始化为 弧尾 指向的第一个边
	ArcNode* p = nodeArr[tail].first;
	//初始化 前一边结点的指针
	ArcNode* q = NULL;
	//重复边布尔值
	bool exist = false;
	//1.边的重复性校验
	while (p != NULL)
	{
		//若已存在该边，则标记为 存在 true
		if (p->adjVex == head)
		{
			exist = true;
			break;
		}
		//若不是该边，继续下一个边校验
		q = p;
		p = p->next;
	}
	//2.1.如果边存在，则跳过，不做插入
	if (exist)
		return;
	//2.2.边不存在时，创建边
	ArcNode* newArc = new ArcNode();
	newArc->srcVex = tail;
	newArc->adjVex = head;
	newArc->weight = weight;
	newArc->next = NULL;
	newArc->front_next = NULL;
	//3.1.插入第一条边
	if (q == NULL)
	{
		nodeArr[tail].first = newArc;
	}
	//3.2.插入后序边
	else
	{
		q->next = newArc;
	}

	//边结点指针：初始化为 弧头 指向的第一个边
	ArcNode* m = nodeArr[head].front;
	//初始化 前一边结点的指针
	ArcNode* n = NULL;
	//重复边布尔值
	bool _exist = false;
	//1.边的重复性校验
	while (m != NULL)
	{
		//若已存在该边，则标记为 存在 true
		if (m->adjVex == head)
		{
			_exist = true;
			break;
		}
		//若不是该边，继续下一个边校验
		n = m;
		m = m->front_next;
	}
	//2.1.如果边存在，则跳过，不做插入
	if (exist)
		return;
	//3.1.插入第一条边
	if (n == NULL)
	{
		nodeArr[head].front = newArc;
	}
	//3.2.插入后序边
	else
	{
		n->front_next = newArc;
	}
	//4.边 计数
	arcNum++;
}
//Display()--显示 图|网
void GraphAdjList::Display()
{
	//初始化边表结点指针
	ArcNode* p = NULL;
	cout << "邻接表：" << endl;

	//遍历顶点表
	for (size_t i = 0; i < nodeArr.size(); i++)
	{
		//空顶点（在删除顶点的操作后会出现此类情况）
		if (nodeArr[i].m_Name == "")
		{
			continue;
		}
		//输出顶点
		cout << "[" << i << "]" << nodeArr[i].m_Name << " ";
		//遍历输出边顶点
		p = nodeArr[i].first;
		while (p != NULL)
		{
			cout << "[" << p->adjVex << "," << p->weight << "] ";
			p = p->next;
		}
		cout << endl;
	}
}
/*****************************************遍历路径*****************************************/
//Classify_node()--将节点进行分类
void GraphAdjList::Classify_node()
{
	//节点分类可以在Read时就做吗？
	for (size_t i = 0; i < nodeArr.size(); i++)
	{
		/*********************将寄存器结点名存放到vexs_ff数组里*********************/
		if ((nodeArr[i].m_Ff != "") && (nodeArr[i].m_Clk_Data != 0))
		{
			this->vexs_ff.push_back(i);
			this->ffNum++;
		}
		/*********************将输出结点名存放到vexs_tail数组里*********************/
		if ((nodeArr[i].m_Name.find("gp") != string::npos) && (nodeArr[i].first == NULL))
		{
			this->vexs_tail.push_back(i);
			this->tailNum++;
		}
		/*********************将输入结点名存放到vexs_head数组里*********************/
		if ((nodeArr[i].m_Name.find("gp") != string::npos) && (nodeArr[i].m_Clk_Data == 0) && nodeArr[i].first != NULL)
		{
			this->vexs_head.push_back(i);
			this->headNum++;
		}
		if ((nodeArr[i].m_Name.find("gp") != string::npos) && (nodeArr[i].m_Clk_Data != 0) && nodeArr[i].first != NULL)
		{
			this->vexs_clk.push_back(i);
			this->clkNum++;
		}
	}
}
//_DFS()--深度优先遍历 非递归
void GraphAdjList::_DFS(int index1, int index2, int path_choice)
{
	this->vexs_visited.clear();
	//2.初始化顶点访问数组
	for (size_t i = 0; i < nodeArr.size(); i++)
	{
		this->vexs_visited.push_back(0);
	}
	vexs_visited[index1] = 1;
	vector<ArcNode*> s;
	//初始化边结点 指针
	ArcNode* p = nodeArr[index1].first;
	while (p != NULL || !s.empty())
	{
		if (vexs_visited[p->adjVex] == 0)  //如果没访问过
		{
			if (p->adjVex != index2)   //如果不是目标点
			{
				vexs_visited[p->adjVex] = 1;
				if (nodeArr[p->adjVex].m_Ff == "ff" && nodeArr[p->adjVex].m_Clk_Data != 0)    //如果不是出发点
				{
					p = p->next;
				}
				else
				{
					s.push_back(p);
					p = nodeArr[p->adjVex].first;
				}
			}
			else  //如果是目标点
			{
				Path.Path_Node.clear();
				for (size_t i = 0; i < s.size(); i++)
				{
					Path.Path_Node.push_back(s[i]);
				}
				Path.Path_Node.push_back(p);
				switch (path_choice)
				{
				case 1:
					this->Path_ff_ff.push_back(Path);
					break;
				case 2:
					this->Path_ff_out.push_back(Path);
					break;
				case 3:
					this->Path_in_ff.push_back(Path);
					break;
				case 4:
					this->Path_in_out.push_back(Path);
					break;
				case 5:
					this->Path_clk_ff.push_back(Path);
					break;
				}
				p = p->next;  //返回现在容器中最后一个元素的下一条边
			}
		}
		else if (p->adjVex == index1)		//如果已访问过
			p = s.back();
		else    //如果已访问过
		{
			p = p->next;
			if (!s.empty())
				s.pop_back();
		}
		if (p == NULL)
		{
			if (!s.empty())
				p = s.back();
			else
				break;
		}
	}
}
//DFS_All_Path()--遍历所有路径
void GraphAdjList::DFS_All_Path()
{
	for (size_t i = 0; i < this->ffNum; i++)
	{
		/****************输出ff->ff的路径****************/
		for (size_t j = i + 1; j < this->ffNum; j++)
		{
			if (nodeArr[vexs_ff[i]].m_Clk_Data == nodeArr[vexs_ff[j]].m_Clk_Data)
			{
				_DFS(vexs_ff[i], vexs_ff[j], 1);
			}
		}
		/****************输出ff->out的路径****************/
		//是否要考虑ff->out中间还有其他组合逻辑的情况？
		for (size_t j = 0; j < this->tailNum; j++)
			_DFS(vexs_ff[i], vexs_tail[j], 2);
	}

	for (size_t i = 0; i < this->headNum; i++)
	{
		/****************输出in->ff的路径****************/
		for (size_t j = 0; j < this->ffNum; j++)
			_DFS(vexs_head[i], vexs_ff[j], 3);
		/****************输出in->out的路径****************/
		for (size_t j = 0; j < this->tailNum; j++)
			_DFS(vexs_head[i], vexs_tail[j], 4);
	}

	for (size_t i = 0; i < this->clkNum; i++)
	{
		/****************输出clk->ff的路径****************/
		for (size_t j = 0; j < this->ffNum; j++)
			_DFS(vexs_clk[i], vexs_ff[j], 5);
	}
}








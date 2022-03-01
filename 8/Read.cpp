#include "Read.h"
#include "GraphAdjList.h"
using namespace std;

extern vector<VexNode> nodeArr;
extern size_t nodeArr_size;
extern vector<ArcData> arcArr;
extern size_t arcArr_size;

struct CLK clkArr[20];
int clkArr_size = 0;
struct TDM tdmArr[3];

//TDM_delay()--计算TDM延时   要改
double TDM_delay(string name, double r)
{
	double delay = 0;
	if (name == "t0")	delay = (20 + r / 4) / 312.5;
	else if (name == "t1")	delay = r / 250;
	else if (name == "t2")	delay = r / 200;
	return delay;
}
//Read()--读取文件，获取相应信息并存存储
void Read()
{
	ifstream ifs;
	string buf;
	stringstream sstream;
	/********************读取design.tdm文件********************/
	tdmArr[0].m_Name = "t0";
	tdmArr[1].m_Name = "t1";
	tdmArr[2].m_Name = "t2";
	/********************读取design.clk文件********************/
	ifs.open(File_clk, ios::in);
	//判断是否打开成功
	if (!ifs.is_open())
	{
		cout << "打开文件失败" << endl;
		return;
	}
	//读取文件内容
	string str_clk_Name, str_clk_Data;
	while (getline(ifs, buf))
	{
		//正则表达式
		regex exp_clk("(c\\d+)\\s+(\\d+\\.?\\d*)");
		//匹配并存储数据
		sregex_iterator iter(buf.begin(), buf.end(), exp_clk);
		sregex_iterator end;
		for (; iter != end; ++iter)
		{
			str_clk_Name = iter->str(1);
			str_clk_Data = iter->str(2);
		}
		clkArr[clkArr_size].m_Name = str_clk_Name;//存储时钟名
		sstream << str_clk_Data;//将字符串型转换为浮点型
		sstream >> clkArr[clkArr_size].m_Data;//存储时钟数据

		sstream.clear();
		clkArr_size++;
	}
	ifs.close();
	/********************读取design.are文件********************/
	ifs.open(File_are, ios::in);
	//判断是否打开成功
	if (!ifs.is_open())
	{
		cout << "打开文件失败" << endl;
		return;
	}
	//读取文件内容
	string str_node_Name, str_node_Ff, str_node_Clk;
	while (getline(ifs, buf))
	{
		//正则表达式
		regex exp_are("(gp?\\d+)\\s.?(f?f?)\\s?(c?\\d?\\d?).?");
		//匹配并存储数据
		sregex_iterator iter(buf.begin(), buf.end(), exp_are);
		sregex_iterator end;
		for (; iter != end; ++iter)
		{
			str_node_Name = iter->str(1);
			str_node_Ff = iter->str(2);
			str_node_Clk = iter->str(3);
		}
		nodeArr.push_back(VexNode{});
		nodeArr[nodeArr_size].m_Name = str_node_Name;
		nodeArr[nodeArr_size].m_Ff = str_node_Ff;
		for (int i = 0; i < clkArr_size; i++)
		{
			if (str_node_Clk == clkArr[i].m_Name)
			{
				nodeArr[nodeArr_size].m_Clk_Name = clkArr[i].m_Name;
				nodeArr[nodeArr_size].m_Clk_Data = clkArr[i].m_Data;
				nodeArr[nodeArr_size].Tcycle = 1000 / nodeArr[nodeArr_size].m_Clk_Data;
			}
		}
		nodeArr_size++;
		
	}
	ifs.close();
	/********************读取design.node文件********************/
	ifs.open(File_node, ios::in);
	//判断是否打开成功
	if (!ifs.is_open())
	{
		cout << "打开文件失败" << endl;
		return;
	}
	//读取文件内容
	string str_node_FPGA;
	while (getline(ifs, buf))
	{
		//正则表达式
		regex exp_node("\\s*F?P?G?A?(\\d*)\\s?T?Y?P?E?\\s*\\d*\\s*\\:*\\s*(gp?\\d+)");
		//匹配并存储数据
		sregex_iterator iter(buf.begin(), buf.end(), exp_node);
		sregex_iterator end;
		for (; iter != end; ++iter)
		{
			str_node_Name = iter->str(2);
			if (iter->str(1) != "")
			{
				str_node_FPGA = iter->str(1);
			}
			for (size_t i = 0; i < nodeArr_size; i++)
			{
				if (str_node_Name == nodeArr[i].m_Name)
				{
					nodeArr[i].m_FPGA = str_node_FPGA;
				}
			}
		}
	}
	ifs.close();
	/********************读取design.net文件********************/
	ifs.open(File_net, ios::in);
	//判断是否打开成功
	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	//读取文件内容
	string str_arc_Head, str_arc_Tail; //s结点/l结点 
	string str_tdm_Name;
	double str_tdm_Data = 0;
	double str_arc_Delay = 0; //延时-权值
	//读到非第一个s时，str_arc_Tail中的内容还是上一个s后的结点名，故设置两个flag
	//flag相同时表示头刚刚改变而尾还没变，不进行权值插入
	bool flag_s_change = 0, flag_l = 1;
	while (getline(ifs, buf))
	{
		//正则表达式
		regex exp_net("(gp?\\d+)\\s(s?l?)\\s*(\\d?)(t\\d)?r?(\\d*)?");
		//匹配并存储数据
		sregex_iterator iter(buf.begin(), buf.end(), exp_net);
		sregex_iterator end;
		for (; iter != end; ++iter)
		{
			if (iter->str(2) == "s")
			{
				str_arc_Tail = iter->str(1); //存入尾缓存
				flag_s_change = 1;
			}
			else if (iter->str(2) == "l")
			{
				str_arc_Head = iter->str(1);  //存入头缓存
				flag_s_change = 0;
				
				if (iter->str(3) != "")
				{
					str_arc_Delay = atof(iter->str(3).c_str());
				}
				else
					str_arc_Delay = 0.f;
			}

			if (iter->str(4) != "")
			{
				str_tdm_Name = iter->str(4);
				sstream << iter->str(5);
				sstream >> str_tdm_Data;
				sstream.clear();
				for (int i = 0; i < clkArr_size; i++)
				{
					if (str_tdm_Name == tdmArr[i].m_Name)
					{
						str_arc_Delay = TDM_delay(str_tdm_Name, str_tdm_Data);
					}
				}
			}
		}
		if ((str_arc_Tail != "") && (flag_s_change != flag_l))
		{
			arcArr.push_back(ArcData{ str_arc_Tail, str_arc_Head, str_arc_Delay });
			arcArr_size++;
		}
	}
	ifs.close();
}
//Print_test()--打印nodeArr内容
void Print_nodeArr()
{
	cout << "Name" << "\t\t" << "clk" << "\t" << "Tcycle" << "\t" << "FPGA" << endl;
	for (size_t i = 0; i < nodeArr.size(); i++)
	{
		cout << nodeArr[i].m_Name << "\t";
		cout << nodeArr[i].m_Ff << "\t";
		cout << nodeArr[i].m_Clk_Name << "\t";
		cout << nodeArr[i].m_Clk_Data << "\t";
		cout << nodeArr[i].Tcycle << "\t";
		cout << nodeArr[i].m_FPGA << endl;
	}
}
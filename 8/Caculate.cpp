#include "GraphAdjList.h"
using namespace std;

extern vector<VexNode> nodeArr;

double Tdp = 0;
double Tc1delay = 0;
double Tc2delay = 0;
ArcNode* p = NULL;
Paths* pt = NULL; 
int path_num = 0;
double Sum_ss = 0;
double Sum_hs = 0;
double Sum_cpd = 0;
double Treq_s = 0;
double Tarr = 0;
double Tss = 0;
double Ths = 0;
double Treq_h = 0;

vector<VexNode> T;  //缓存
//违例路径结构体
struct Path_Critical
{
	vector<VexNode>Path_Node;
	double Treq_s = 0;    
	double Treq_h = 0;
	double Tarr = 0;
	double Tss = 0;
	double Ths = 0;
};
//因输出方式不同，纯组合路径结构体单独存放
struct  Path_io
{
	vector<VexNode>Path_Node;
	double Tio = 0;
};
vector<Path_Critical> Path_Cri;    //所有违例路径数组
vector<Path_io> Path_Com;		//所有组合路径数组

//Calc_path()--计算路径
void GraphAdjList::Calc_path()
{
	/***************************计算ff->ff*****************************/
	for (size_t i = 0; i < this->Path_clk_ff.size(); i++)
	{
		pt = &Path_clk_ff[i];
		for (size_t j = 0; j < pt->Path_Node.size(); j++)
		{
			p = pt->Path_Node[j];
			nodeArr[p->adjVex].m_Clk_Delay = p->weight;
		}
	}
	for (size_t i = 0; i < this->Path_ff_ff.size(); i++)
	{
		Tdp = 0;
		pt = &Path_ff_ff[i];

		Tc1delay = nodeArr[pt->Path_Node[0]->srcVex].m_Clk_Delay;
		if (Tc1delay != 0)
			Tdp = Tc1delay;
		
		Tdp += Tco;
	
		nodeArr[pt->Path_Node[0]->srcVex].m_fixed_delay = Tco;

		for (size_t j = 0; j < pt->Path_Node.size(); j++)
		{
			p = pt->Path_Node[j];

			if (nodeArr[p->adjVex].m_Ff == "")
			{
				Tdp += p->weight;
				nodeArr[p->srcVex].m_wire_delay = p->weight;
				nodeArr[p->srcVex].Tdp = Tdp;
				T.push_back(nodeArr[p->srcVex]);  
				
				Tdp += Tcomb;

				nodeArr[p->adjVex].m_fixed_delay = Tcomb;
				nodeArr[p->adjVex].Tdp = Tdp;
			
			}
			else
			{
				Tdp += p->weight;
				nodeArr[p->srcVex].m_wire_delay = p->weight;
				nodeArr[p->srcVex].Tdp = Tdp;
				T.push_back(nodeArr[p->srcVex]);
			}
		}
		T.push_back(nodeArr[p->adjVex]);
/*****************************************************************************************************/
		//计算Setup Slack
		Tc2delay = nodeArr[p->adjVex].m_Clk_Delay;
		Treq_s = nodeArr[p->adjVex].Tcycle + Tc2delay - Tsu;
		Tarr = Tdp;
		Tss = Treq_s - Tarr;
		//计算Hold Slack
		Treq_h = Tc2delay + Thd
		Ths = Tarr - Treq_h;

		//判断是否违例
		//if ((pt->Tss < 0) || (pt->Ths) < 0)
		//{
			Path_Cri.push_back({T,Treq_s,Treq_h,Tarr,Tss,Ths});
			
			T.clear();
			
			Sum_ss += Tss;
			Sum_hs += Ths;
		//}
	}

	/***************************计算ff->out*****************************/
	for (size_t i = 0; i < this->Path_ff_out.size(); i++)
	{
		Tdp = 0;
		pt = &Path_ff_out[i];

		Tc1delay = nodeArr[pt->Path_Node[0]->srcVex].m_Clk_Delay;
		Tdp = Tc1delay;

		Tdp += Tco;
		nodeArr[pt->Path_Node[0]->srcVex].m_fixed_delay = Tco;

		for (size_t j = 0; j < pt->Path_Node.size(); j++)
		{
			p = pt->Path_Node[j];
			if (nodeArr[p->adjVex].m_Ff == "" && nodeArr[p->adjVex].m_Name.find("gp") == string::npos)
			{
				Tdp += p->weight;
				nodeArr[p->srcVex].m_wire_delay = p->weight;
				nodeArr[p->srcVex].Tdp = Tdp;

				Tdp += Tcomb;
				nodeArr[p->adjVex].m_fixed_delay = Tcomb;
				nodeArr[p->adjVex].Tdp = Tdp;

				T.push_back(nodeArr[p->srcVex]);
			}
			else
			{
				Tdp += p->weight;
				nodeArr[p->srcVex].m_wire_delay = p->weight;
				nodeArr[p->srcVex].Tdp = Tdp;
				T.push_back(nodeArr[p->srcVex]);
			}
		}
		T.push_back(nodeArr[p->adjVex]);

		//计算Setup Slack
		
		Treq_s = nodeArr[pt->Path_Node[0]->srcVex].Tcycle + Tc1delay - Tsu;
		Tarr = Tdp;        //ff->out计算就这里和ff->ff不一样，后续再考虑是否合并
		Tss = Treq_s - Tarr;
		//计算Hold Slack
		Treq_h = Tc1delay + Thd;
		Ths = Tarr - Treq_h;

		//判断是否违例
		//if ((pt->Tss < 0) || (pt->Ths) < 0)
		//{
			Path_Cri.push_back({ T,Treq_s,Treq_h,Tarr,Tss,Ths });

			T.clear();
			
			Sum_ss += Tss;
			Sum_hs += Ths;
		//}
	}

	/***************************计算in->ff*****************************/
	for (size_t i = 0; i < this->Path_in_ff.size(); i++)
	{
		Tdp = 0;
		pt = &Path_in_ff[i];
		nodeArr[pt->Path_Node[0]->srcVex].m_fixed_delay = Tco;

		for (size_t j = 0; j < pt->Path_Node.size(); j++)
		{
			p = pt->Path_Node[j];

			if (nodeArr[p->adjVex].m_Ff == "" && nodeArr[p->adjVex].m_Name.find("gp") == string::npos)
			{
				Tdp += p->weight;
				nodeArr[p->srcVex].m_wire_delay = p->weight;
				nodeArr[p->srcVex].Tdp = Tdp;

				Tdp += Tcomb;
				nodeArr[p->adjVex].m_fixed_delay = Tcomb;
				nodeArr[p->adjVex].Tdp = Tdp;
			}
			else
			{
				Tdp += p->weight;
				nodeArr[p->srcVex].m_wire_delay = p->weight;
				nodeArr[p->srcVex].Tdp = Tdp;
				T.push_back(nodeArr[p->srcVex]);
			}
		}
		T.push_back(nodeArr[p->adjVex]);

		//计算Setup Slack
		Tc2delay = nodeArr[p->adjVex].m_Clk_Delay;
		Treq_s = nodeArr[p->adjVex].Tcycle + Tc2delay - Tsu;
		Tarr = Tdp + Tc2delay + Tco;  //in->ff和ff->ff这些不一样，后续再考虑是否合并      
		Tss = Treq_s - Tarr;
		//计算Hold Slack
		Treq_h = Tc2delay + Thd;
		Ths = Tarr - Treq_h;;

		//判断是否违例
		//if ((pt->Tss < 0) || (pt->Ths) < 0)
		//{
			Path_Cri.push_back({ T,Treq_s,Treq_h,Tarr,Tss,Ths });

			T.clear();
			
			Sum_ss += Tss;
			Sum_hs += Ths;
		//}
	}

	/***************************计算in->out*****************************/
	for (size_t i = 0; i < this->Path_in_out.size(); i++)
	{
		Tdp = 0;
		pt = &Path_in_out[i];
		for (size_t j = 0; j < pt->Path_Node.size(); j++)
		{
			p = pt->Path_Node[j];
			
				Tdp += p->weight;
				nodeArr[p->srcVex].m_wire_delay = p->weight;
				nodeArr[p->srcVex].Tdp = Tdp;
				if (j != pt->Path_Node.size() - 1)
				{
					Tdp += Tcomb;
					nodeArr[p->adjVex].m_fixed_delay = Tcomb;
					nodeArr[p->adjVex].Tdp = Tdp;
				}
				T.push_back(nodeArr[p->srcVex]);
			
		}
			T.push_back(nodeArr[p->adjVex]);
			Path_Com.push_back({ T,Tdp });
			T.clear();
			
			Sum_cpd += Tdp;
	
	}

	/******************************输出文件*************************************/
	ofstream ofs;
	ofs.open("sta_report.txt", ios::out | ios::trunc);
	//在开头加信息
	ofs.seekp(0, ios::beg);
	ofs << "Total: " << endl
		<< "Setup Slack: " << Sum_ss << "ns" << endl
		<< "Hold Slack: " << Sum_hs << "ns" << endl
		<< "Combinal Port Delay: " << Sum_cpd << "ns" << endl;
	ofs << endl;
	
	for (size_t i = 0; i < Path_Cri.size(); ++i)
	{
		T = Path_Cri[i].Path_Node;
		/**************************setup slack*************************/
		path_num++;
		ofs << "Path" << path_num << ": " << endl;
		ofs << "Data Arrival Time:" << endl;
		for (size_t j = 0; j < T.size() - 1; ++j)
		{
			if (T[j].m_Clk_Delay != 0)
			{
				ofs << "@cable" << "\t\t" << T[j].m_Clk_Delay << "\t" << T[j].m_Clk_Delay << endl;
				ofs << T[j].m_Name << "@FPGA" << T[j].m_FPGA << "\t" << "+" << 1.0 << "\t" << Tc1delay + T[j].m_fixed_delay << endl;
			}
			else if (j == 0)
				ofs << T[j].m_Name << "@FPGA" << T[j].m_FPGA << "\t" << T[j].m_fixed_delay << "\t" << T[j].m_fixed_delay << endl;
			else
				ofs << T[j].m_Name << "@FPGA" << T[j].m_FPGA << "\t" << "+0.1" << "\t" << T[j - 1].Tdp + 0.1 << endl;

			if (T[j].m_wire_delay != 0)
				ofs << "@cable" << "\t\t" << "+" << T[j].m_wire_delay << "\t" << T[j].Tdp << endl;
		}
		ofs << "Data Expected Time:" << endl;
		if (T.back().m_Clk_Name != "")
		{
			ofs << T.back().m_Clk_Name << "  rise edge" << "\t" << T.back().Tcycle << "\t" << T.back().Tcycle << endl;
			if(T.back().m_Clk_Delay != 0)
				ofs << "@cable" << "\t\t" << "+" << T.back().m_Clk_Delay << "\t" << T.back().Tcycle + T.back().m_Clk_Delay << endl;
			
			ofs << T.back().m_Name << "  Tsu" << "\t\t" << "-1.0" << "\t" << Path_Cri[i].Treq_s << endl;
		}
		else
		{
			ofs << T.front().m_Clk_Name << "  rise edge" << "\t" << T.front().Tcycle << "\t" << T.front().Tcycle << endl;
			ofs << "@cable" << "\t\t" << "+" << T.front().m_Clk_Delay << "\t" << T.front().Tcycle + T.front().m_Clk_Delay << endl;
			ofs << T.back().m_Name << "  Tsu" << "\t\t" << "-1.0" << "\t" << Path_Cri[i].Treq_s << endl;
		}
		ofs << "----------------------------------------------------------------------------" << endl;
		ofs << "setup slack: " << Path_Cri[i].Tss << endl;
		ofs << "============================================================================" << endl;


		/**************************hold slack*************************/
		path_num++;
		ofs << "Path" << path_num << ": " << endl;
		ofs << "Data Arrival Time:" << endl;
		for (size_t j = 0; j < T.size() - 1; ++j)
		{
			if (T[j].m_Clk_Delay != 0)
			{
				ofs << "@cable" << "\t\t" << T[j].m_Clk_Delay << "\t" << T[j].m_Clk_Delay << endl;
				ofs << T[j].m_Name << "@FPGA" << T[j].m_FPGA << "\t" << "+" << 1.0 << "\t" << Tc1delay + T[j].m_fixed_delay << endl;
			}
			else if (j == 0)
				ofs << T[j].m_Name << "@FPGA" << T[j].m_FPGA << "\t" << T[j].m_fixed_delay << "\t" << T[j].m_fixed_delay << endl;
			else
				ofs << T[j].m_Name << "@FPGA" << T[j].m_FPGA << "\t" << "+0.1" << "\t" << T[j - 1].Tdp + 0.1 << endl;

			if (T[j].m_wire_delay != 0)
				ofs << "@cable" << "\t\t" << "+" << T[j].m_wire_delay << "\t" << T[j].Tdp << endl;
		}
		ofs << "Data Expected Time:" << endl;
		if (T.back().m_Clk_Name != "")    //ff->ff,in->ff
		{
			if (T.back().m_Clk_Delay != 0)
				ofs << "@cable" << "\t\t" << T.back().m_Clk_Delay << "\t" << T.back().m_Clk_Delay << endl;
			ofs << T.back().m_Name << "  Thold" << "\t" << "+1.0" << "\t" << Path_Cri[i].Treq_h << endl;
		}
		else    //ff->out
		{
			if (T.front().m_Clk_Delay != 0)
				ofs << "@cable" << "\t\t" << "+" << T.front().m_Clk_Delay << "\t" << T.front().m_Clk_Delay << endl;
			ofs << T.back().m_Name << "  Thold" << "\t" << "+1.0" << "\t" << Path_Cri[i].Treq_h << endl;
		}
		ofs << "----------------------------------------------------------------------------" << endl;
		ofs << "hold slack: " << Path_Cri[i].Ths << endl;
		ofs << "============================================================================" << endl;

	}
	/**************************Combinational Delay*************************/
	for (size_t i = 0; i < Path_Com.size(); ++i)
	{
		T = Path_Com[i].Path_Node;
		path_num++;
		ofs << "Path" << path_num << ": " << endl;
		for (size_t j = 1; j < T.size()-1; ++j)
		{
			ofs << T[j].m_Name << "@FPGA" << T[j].m_FPGA << "\t" << T[j].m_fixed_delay << "\t" << T[j].m_fixed_delay << endl;
		}
		ofs << "----------------------------------------------------------------------------" << endl;
		ofs << "Combinal Port Delay: " << Path_Com[i].Tio << endl;
		ofs << "============================================================================" << endl;
	}
	ofs.close();
}


//Print_path()--打印路径信息
//void GraphAdjList::Print_path()
//{
//	/*********************打印ff->ff路径信息*********************/
//	cout << "ff->ff: " << endl << endl;
//	for (size_t i = 0; i < Path_ff_ff.size(); i++)
//	{
//		pt = &Path_ff_ff[i];
//		for (size_t j = 0; j < pt->Path_Node.size(); j++)
//		{
//			p = pt->Path_Node[j];
//			cout << nodeArr[p->srcVex].m_Name << " " << nodeArr[p->adjVex].m_Name << " ";
//		}
//		cout << endl;
//		cout << "setup slack: " << pt->Treq << " " << pt->Tarr << " " << pt->Tss << "  ";
//		cout << "hold slack: " << pt->Tarr << " " << 1 << " " << pt->Ths << " " << endl;
//	}
//	/*********************打印ff->out路径信息*********************/
//	cout << endl << endl << "ff->out: " << endl << endl;
//	for (size_t i = 0; i < Path_ff_out.size(); i++)
//	{
//		pt = &Path_ff_out[i];
//		for (size_t j = 0; j < pt->Path_Node.size(); j++)
//		{
//			p = pt->Path_Node[j];
//			cout << nodeArr[p->srcVex].m_Name << " " << nodeArr[p->adjVex].m_Name << " ";
//		}
//		cout << endl;
//		cout << "setup slack: " << pt->Treq << " " << pt->Tarr << " " << pt->Tss << "  ";
//		cout << "hold slack: " << pt->Tarr << " " << 1 << " " << pt->Ths << " " << endl;
//	}
//	/*********************打印in->ff路径信息*********************/
//	cout << endl << endl << "in->ff: " << endl << endl;
//	for (size_t i = 0; i < Path_in_ff.size(); i++)
//	{
//		pt = &Path_in_ff[i];
//		for (size_t j = 0; j < pt->Path_Node.size(); j++)
//		{
//			p = pt->Path_Node[j];
//			cout << nodeArr[p->srcVex].m_Name << " " << nodeArr[p->adjVex].m_Name << " ";
//		}
//		cout << endl;
//		cout << "setup slack: " << pt->Treq << " " << pt->Tarr << " " << pt->Tss << "  ";
//		cout << "hold slack: " << pt->Tarr << " " << 1 << " " << pt->Ths << " " << endl;
//	}
//	/*********************打印in->out路径信息*********************/
//	cout << endl << endl << "in->out: " << endl << endl;
//	for (size_t i = 0; i < Path_in_out.size(); i++)
//	{
//		pt = &Path_in_out[i];
//		for (size_t j = 0; j < pt->Path_Node.size(); j++)
//		{
//			p = pt->Path_Node[j];
//			cout << nodeArr[p->srcVex].m_Name << " " << nodeArr[p->adjVex].m_Name << " ";
//		}
//		cout << pt->Tcpd << endl;
//	}
//}
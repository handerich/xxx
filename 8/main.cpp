#include <iostream>
#include "Read.h"
#include "GraphAdjList.h"
using namespace std;

vector<VexNode> nodeArr; //结点表（顶点表）
size_t nodeArr_size;
vector<ArcData> arcArr;  //边列表
size_t arcArr_size;
GraphAdjList* dn = new GraphAdjList(); //图

int main()
{
	Read();
	//Print_nodeArr();

	dn->_CreateDN(arcArr);
	//dn->Display();

	dn->Classify_node();
	dn->DFS_All_Path();
	
	dn->Calc_path();
	//dn->Print_path();

	system("pause");
	return 0;
}
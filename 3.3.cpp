#include<iostream>
using namespace std; 
//---------图的邻接矩阵存储表示----------
#define MaxInt 32767                                              //表示极大值
#define MVNum 100                                                 //最大顶点数
#define OK 1
typedef char VerTexType;                                          //假设顶点的数据类型为字符型
typedef int ArcType;                                              //假设边的权值为整型
typedef int Status;
typedef struct          
{
	VerTexType vexs[MVNum];                                       //顶点表
	ArcType arcs[MVNum][MVNum];                                   //邻接矩阵
	int vexnum,arcnum;                                            //图的当前点数和边数
}AMGraph;
//---------查找顶点V在图中的位置----------
Status LocateVex(AMGraph G,int v)
{
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vexs[i]==v)                                          //图G存在，v和G中顶点有相同特征
			return i;                                             //返回该顶点在图的位置
	}
	return -1;
}
//---------采用邻接矩阵创建双向有向网---------
Status CreateUDN(AMGraph &G)
{
	int i,j,k; 
	char v1[10]={'A','A','A','B','B','C','C','D','E','F'};
	char v2[10]={'B','C','D','C','E','D','F','G','F','G'};
	int w[10]={2553,700,704,511,812,349,1579,651,2368,1385};
    G.vexnum=7; G.arcnum=10;                                      //总顶点数，总边数
	for(i=0;i<G.vexnum;++i)                                       //依次输入点的信息
		G.vexs[i]=65+i;                                           
		for(i=0;i<G.vexnum;++i)                                   //初始化邻接矩阵，边的权值均置为极大值MaxInt
			for(j=0;j<G.vexnum;++j)
				G.arcs[i][j]=MaxInt;                              //构建邻接矩阵
	for(k=0;k<G.arcnum;++k)
	{
		 //输入一条边依附的顶点及权值
		i=LocateVex(G,v1[k]);j=LocateVex(G,v2[k]);                //确定v1和v2在G中的位置，即顶点数组的下标
		G.arcs[j][i]=G.arcs[i][j]=w[k];                           //边<v1，v2>的权值为w
	}
	return OK;
}
//用迪杰斯特拉算法求有向网G的v0顶点到其余顶点的最短路径
void ShortestPath_DIJ(AMGraph G,int v0)
{
	int i,t,j,w,n,v,min;
	int Path[7],S[7],D[7],a[6];
	n=G.vexnum; j=0;                                              //n为G中顶点的个数
	for(v=0;v<n;++v)                                              //n个顶点依次初始化
	{ 
		S[v]=false;                                               //S初始为空集
		D[v]=G.arcs[v0][v];                                       //将v0到各个终点的最短路径长度初始化为弧上的权值
		if(D[v]<MaxInt) Path[v]=0;                                //如果v0和v之间有弧，则将v的前驱为v0
		else Path[v]=-1;                                          //如果v0和v之间无弧，则将v的前驱为-1
	}
	S[v0]=true;                                                   //将v0加入S  
	D[v0]=0;                                                      //源点到源点的距离为0 

//--------初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集-------

	for(i=1;i<n;++i)                                              //对其余n-1个顶点，依次进行计算
	{
		min=MaxInt;
		for(w=0;w<n;++w)
			if(!S[w]&&D[w]<min)
			{v=w;min=D[w];}                                       //选择一条当前的最短路径，终点为v
		S[v]=true;                                                //将v加入S

		for(w=0;w<n;++w)                                          //更新从v0出发到集合V-S上所有顶点的最短路径长度
			if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
			{
				D[w]=D[v]+G.arcs[v][w];                           //更新D[w]
				Path[w]=v;                                        //更改w的前驱为v
			}
	}
//----------输出最短路径以及距离，并按照距离从大到小的顺序排序--------


	for(i=0;i<n;i++)
		if(v0!=i)                                                 //排除它本身
			if(D[i]!=MaxInt)	
				a[j++]=i;		                                  //将具有权值的下标存在数组a	
	for(i=0;i<j;i++)
		for(int u=i;u<j;u++)
			if(D[a[i]]<D[a[u]])                                   //将权值大的下标放在前面
			{t=a[i];a[i]=a[u];a[u]=t;}
	cout<<"\n按照距离从大到小为："<<endl<<endl;
	cout<<"路径长度     路径"<<endl;
	for(i=0;i<j;i++)
	{
		printf("%5d",D[a[i]]);
		printf("     %5c",G.vexs[a[i]]);
		v=Path[a[i]];                                            //将Path所对应的位置赋给V
		while(v!=0)                                              //判断是否有中继点
		{
			cout<<"<-"<<G.vexs[v];
			v=Path[v];                                           //更新V
		}
		cout<<"<-"<<G.vexs[v0]<<endl;

	}
}
//用弗洛伊德算法求有向网G中的各顶点i和j之间的最短路径
void ShortestPath_Floyd(AMGraph G,int v0,int v1)
{
	int i,j,k,v;
	int D[7][7],Path[7][7];
	for(i=0;i<G.vexnum;++i)                                       //各对结点之间初始已知路径及距离
		for(j=0;j<G.vexnum;++j)
		{
			D[i][j]=G.arcs[i][j];
			if(D[i][j]<MaxInt&& i!=j) Path[i][j]=i;               //如果i和j之间有弧，则将j的前驱置为1
			else Path[i][j]=-1;                                   //如果i和j之间无弧，则将j的前驱置为-1
		}
	for(k=0;k<G.vexnum;++k)
		for(i=0;i<G.vexnum;++i)
			for(j=0;j<G.vexnum;++j)
				if(D[i][k]+D[k][j]<D[i][j])                       //从i经k到j的一条路径更短
				{
					D[i][j]=D[i][k]+D[k][j];                      //更新D[i][j]
					Path[i][j]=Path[k][j];                        //更改j的前驱为k
				}
	
	cout<<"起点城市："<<G.vexs[v0]<<"   终点城市："<<G.vexs[v1]<<endl;
	if(Path[v0][v1]!=-1)
	{
		cout<<"两地的距离为："<<D[v0][v1]<<endl;
		cout<<"路线："<<G.vexs[v1];
		v=Path[v0][v1];                                           //将Path的位置赋给V
		while(v!=v0)                                              //判断是否有中继点
		{
			cout<<"<-"<<G.vexs[v];
			v=Path[v0][v];                                        //更新V
		}
		cout<<"<-"<<G.vexs[v0]<<endl<<endl;
	}
	else cout<<"无法到达该城市"<<endl;


}
//----------------构建菜单---------------
int menu()
{
	int n;
	cout<<"---欢迎登录交通咨询系统---"<<endl<<endl;
	cout<<"请选择功能："<<endl;
	cout<<"1.某地到其他地方的最短路径和距离"<<endl;
	cout<<"2.两地之间的最短路径和距离"<<endl;
	cout<<"0.退出交通咨询系统"<<endl;
	cin>>n; return n;
}
main()
{
	AMGraph G;int v0,v1;
	char ch;
	CreateUDN(G);                                                //构建邻接矩阵
	while(1)
	{
		switch(menu())
		{
		case 1:	cout<<"请输入需要查找的城市（ABCDEFG）：";
		     	cin>>ch;v0=ch-65;                                //输入地点，将位置存放在V0中
		    	ShortestPath_DIJ(G,v0);	   break;                //迪杰斯特拉算法
		case 2: cout<<"请输入从哪个城市出发（ABCDEFG）：";
			    cin>>ch;v0=ch-65;                                //输入起点城市，将位置存放在v0
		    	cout<<"\n请输入到哪个城市(ABCDEFG)：";           //输入终点城市，将位置存放在v1
		    	cin>>ch;v1=ch-65;
				ShortestPath_Floyd(G,v0,v1);break;               //弗洛伊德算法
		case 0: cout<<"正在退出...请稍后"<<endl;exit(0);break;
		default: cout<<"输入错误...即将退出系统"<<endl;exit(0);
		}
	}
}
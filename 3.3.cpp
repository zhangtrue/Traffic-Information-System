#include<iostream>
using namespace std; 
//---------ͼ���ڽӾ���洢��ʾ----------
#define MaxInt 32767                                              //��ʾ����ֵ
#define MVNum 100                                                 //��󶥵���
#define OK 1
typedef char VerTexType;                                          //���趥�����������Ϊ�ַ���
typedef int ArcType;                                              //����ߵ�ȨֵΪ����
typedef int Status;
typedef struct          
{
	VerTexType vexs[MVNum];                                       //�����
	ArcType arcs[MVNum][MVNum];                                   //�ڽӾ���
	int vexnum,arcnum;                                            //ͼ�ĵ�ǰ�����ͱ���
}AMGraph;
//---------���Ҷ���V��ͼ�е�λ��----------
Status LocateVex(AMGraph G,int v)
{
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vexs[i]==v)                                          //ͼG���ڣ�v��G�ж�������ͬ����
			return i;                                             //���ظö�����ͼ��λ��
	}
	return -1;
}
//---------�����ڽӾ��󴴽�˫��������---------
Status CreateUDN(AMGraph &G)
{
	int i,j,k; 
	char v1[10]={'A','A','A','B','B','C','C','D','E','F'};
	char v2[10]={'B','C','D','C','E','D','F','G','F','G'};
	int w[10]={2553,700,704,511,812,349,1579,651,2368,1385};
    G.vexnum=7; G.arcnum=10;                                      //�ܶ��������ܱ���
	for(i=0;i<G.vexnum;++i)                                       //������������Ϣ
		G.vexs[i]=65+i;                                           
		for(i=0;i<G.vexnum;++i)                                   //��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ����ֵMaxInt
			for(j=0;j<G.vexnum;++j)
				G.arcs[i][j]=MaxInt;                              //�����ڽӾ���
	for(k=0;k<G.arcnum;++k)
	{
		 //����һ���������Ķ��㼰Ȩֵ
		i=LocateVex(G,v1[k]);j=LocateVex(G,v2[k]);                //ȷ��v1��v2��G�е�λ�ã�������������±�
		G.arcs[j][i]=G.arcs[i][j]=w[k];                           //��<v1��v2>��ȨֵΪw
	}
	return OK;
}
//�õϽ�˹�����㷨��������G��v0���㵽���ඥ������·��
void ShortestPath_DIJ(AMGraph G,int v0)
{
	int i,t,j,w,n,v,min;
	int Path[7],S[7],D[7],a[6];
	n=G.vexnum; j=0;                                              //nΪG�ж���ĸ���
	for(v=0;v<n;++v)                                              //n���������γ�ʼ��
	{ 
		S[v]=false;                                               //S��ʼΪ�ռ�
		D[v]=G.arcs[v0][v];                                       //��v0�������յ�����·�����ȳ�ʼ��Ϊ���ϵ�Ȩֵ
		if(D[v]<MaxInt) Path[v]=0;                                //���v0��v֮���л�����v��ǰ��Ϊv0
		else Path[v]=-1;                                          //���v0��v֮���޻�����v��ǰ��Ϊ-1
	}
	S[v0]=true;                                                   //��v0����S  
	D[v0]=0;                                                      //Դ�㵽Դ��ľ���Ϊ0 

//--------��ʼ����������ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v�ӵ�S��-------

	for(i=1;i<n;++i)                                              //������n-1�����㣬���ν��м���
	{
		min=MaxInt;
		for(w=0;w<n;++w)
			if(!S[w]&&D[w]<min)
			{v=w;min=D[w];}                                       //ѡ��һ����ǰ�����·�����յ�Ϊv
		S[v]=true;                                                //��v����S

		for(w=0;w<n;++w)                                          //���´�v0����������V-S�����ж�������·������
			if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
			{
				D[w]=D[v]+G.arcs[v][w];                           //����D[w]
				Path[w]=v;                                        //����w��ǰ��Ϊv
			}
	}
//----------������·���Լ����룬�����վ���Ӵ�С��˳������--------


	for(i=0;i<n;i++)
		if(v0!=i)                                                 //�ų�������
			if(D[i]!=MaxInt)	
				a[j++]=i;		                                  //������Ȩֵ���±��������a	
	for(i=0;i<j;i++)
		for(int u=i;u<j;u++)
			if(D[a[i]]<D[a[u]])                                   //��Ȩֵ����±����ǰ��
			{t=a[i];a[i]=a[u];a[u]=t;}
	cout<<"\n���վ���Ӵ�СΪ��"<<endl<<endl;
	cout<<"·������     ·��"<<endl;
	for(i=0;i<j;i++)
	{
		printf("%5d",D[a[i]]);
		printf("     %5c",G.vexs[a[i]]);
		v=Path[a[i]];                                            //��Path����Ӧ��λ�ø���V
		while(v!=0)                                              //�ж��Ƿ����м̵�
		{
			cout<<"<-"<<G.vexs[v];
			v=Path[v];                                           //����V
		}
		cout<<"<-"<<G.vexs[v0]<<endl;

	}
}
//�ø��������㷨��������G�еĸ�����i��j֮������·��
void ShortestPath_Floyd(AMGraph G,int v0,int v1)
{
	int i,j,k,v;
	int D[7][7],Path[7][7];
	for(i=0;i<G.vexnum;++i)                                       //���Խ��֮���ʼ��֪·��������
		for(j=0;j<G.vexnum;++j)
		{
			D[i][j]=G.arcs[i][j];
			if(D[i][j]<MaxInt&& i!=j) Path[i][j]=i;               //���i��j֮���л�����j��ǰ����Ϊ1
			else Path[i][j]=-1;                                   //���i��j֮���޻�����j��ǰ����Ϊ-1
		}
	for(k=0;k<G.vexnum;++k)
		for(i=0;i<G.vexnum;++i)
			for(j=0;j<G.vexnum;++j)
				if(D[i][k]+D[k][j]<D[i][j])                       //��i��k��j��һ��·������
				{
					D[i][j]=D[i][k]+D[k][j];                      //����D[i][j]
					Path[i][j]=Path[k][j];                        //����j��ǰ��Ϊk
				}
	
	cout<<"�����У�"<<G.vexs[v0]<<"   �յ���У�"<<G.vexs[v1]<<endl;
	if(Path[v0][v1]!=-1)
	{
		cout<<"���صľ���Ϊ��"<<D[v0][v1]<<endl;
		cout<<"·�ߣ�"<<G.vexs[v1];
		v=Path[v0][v1];                                           //��Path��λ�ø���V
		while(v!=v0)                                              //�ж��Ƿ����м̵�
		{
			cout<<"<-"<<G.vexs[v];
			v=Path[v0][v];                                        //����V
		}
		cout<<"<-"<<G.vexs[v0]<<endl<<endl;
	}
	else cout<<"�޷�����ó���"<<endl;


}
//----------------�����˵�---------------
int menu()
{
	int n;
	cout<<"---��ӭ��¼��ͨ��ѯϵͳ---"<<endl<<endl;
	cout<<"��ѡ���ܣ�"<<endl;
	cout<<"1.ĳ�ص������ط������·���;���"<<endl;
	cout<<"2.����֮������·���;���"<<endl;
	cout<<"0.�˳���ͨ��ѯϵͳ"<<endl;
	cin>>n; return n;
}
main()
{
	AMGraph G;int v0,v1;
	char ch;
	CreateUDN(G);                                                //�����ڽӾ���
	while(1)
	{
		switch(menu())
		{
		case 1:	cout<<"��������Ҫ���ҵĳ��У�ABCDEFG����";
		     	cin>>ch;v0=ch-65;                                //����ص㣬��λ�ô����V0��
		    	ShortestPath_DIJ(G,v0);	   break;                //�Ͻ�˹�����㷨
		case 2: cout<<"��������ĸ����г�����ABCDEFG����";
			    cin>>ch;v0=ch-65;                                //���������У���λ�ô����v0
		    	cout<<"\n�����뵽�ĸ�����(ABCDEFG)��";           //�����յ���У���λ�ô����v1
		    	cin>>ch;v1=ch-65;
				ShortestPath_Floyd(G,v0,v1);break;               //���������㷨
		case 0: cout<<"�����˳�...���Ժ�"<<endl;exit(0);break;
		default: cout<<"�������...�����˳�ϵͳ"<<endl;exit(0);
		}
	}
}
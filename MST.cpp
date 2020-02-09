#include <iostream>
#include <algorithm>
#define Vmax 1000
#define Emax 500000
using namespace std;

struct edge{
	int u,v,w;  //u:一个端点；v:另一个端点；w:边权 
}E[Emax];

bool cmp(edge a,edge b){
	return a.w<b.w;  //边按照从小到大排序 
}

int m,n; //m:边的条数，n:点的个数 
int sum,edgenum; //sum:边权和，edgenum:已经遍历的边的数量 

//利用并查集实现findroot函数
int root[Vmax];
int findroot(int v){
	if(v==root[v]){  //找到了根节点 
		return v;
	}
	//路径压缩 
	else{
		int Root=findroot(root[v]); //寻找上一级的根节点 
		root[v]=Root;  //更新路上所有节点接入根节点 
		return Root;
	}
}

//实现unionroot函数(对于编号为i的边)
int unionroot(int i){
	int uroot=findroot(E[i].u);
	int vroot=findroot(E[i].v);
	if(uroot!=vroot){
		root[uroot]=vroot;
		sum=sum+E[i].w;
		edgenum=edgenum+1;
	}
} 

int main(){
	//读入点数、边数、边的信息 
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>E[i].u>>E[i].v>>E[i].w;
	}
	
	for(int i=0;i<n;i++){ //初始化并查集
		root[i]=i;
	}
	
	sort(E,E+m,cmp); //边从小到大排序
	
	for(int i=0;i<m;i++){ //遍历边，进行合并操作 
		unionroot(i);
		if(edgenum==n-1){  //边的数量已经达到n-1 
			break;
		} 
	}
	if(edgenum!=n-1){  //若图不连通 
		cout<<"MST does not exist!"<<endl;
	}
	else{
		cout<<"the minimum sum of weights is："<<sum<<endl;
	}
	return 0;
}

 

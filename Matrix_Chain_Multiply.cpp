#include <iostream>
#include <utility>
#define INF 100000
#define N 6
using namespace std;

int opt[N][N], record[N][N]; //opt：最优解矩阵，record：用于记录括号位置
pair<int, int> p0[N]; //记录每个矩阵的大小
int p[N+1]; //存储矩阵大小序列

void opt_generate(int p[N+1], int opt[N][N], int record[N][N]){
	for(int i=0;i<N;i++){
		opt[i][i]=0; //对角线开销置0 
	}
	for(int i=0;i<N;i++){
		record[i][i]=i; //每个元素开始时括号为自己 
	} 
	/*沿斜线方向更新最优解矩阵*/
	for(int i=1;i<N;i++){  //i代表离斜对角线的距离 
		for(int j=0;j<N-i;j++){ //j代表当前三角形开始点的纵坐标 
			int z=j+i; //z代表长度为i时，三角形结束纵坐标 
			opt[j][z]=INF; //初始值为无穷大 
			for(int k=j;k<z;k++){ //选择断点k，寻找最优解 
				int opt_t=opt[j][k]+opt[k+1][z]+p[j]*p[k+1]*p[z+1];
				if(opt_t<opt[j][z]){
					opt[j][z]=opt_t;
					record[j][z]=k;	 //保存断点k 
				} 
			} 
		} 
	} 
}

//打印出括号序列 
void print(int record[N][N], int i,int j){
	if(i==j){
		cout<<"A"<<i;
	} 
	else{
		cout<<"(";
		print(record,i,record[i][j]); //左边寻找 
		print(record,record[i][j]+1,j); //右边寻找 
		cout<<")";
	}
}

int main(){
	for(int i=0;i<N;i++){
		cin>>p0[i].first;
		cin>>p0[i].second;
	}
	
	//如果输入不合法，汇报错误 
	for(int i=1;i<N;i++){
		if(p0[i].first!=p0[i-1].second){
			cout<<"This matrix can not multiplication."<<endl;
			return 0;
		}
	} 
	
	//生成矩阵大小序列 
	for(int i=0;i<N;i++){
		p[i]=p0[i].first; 
	}
	p[N]=p0[N-1].second;
	
	opt_generate(p,opt,record);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<opt[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<N;++i){
		for(int j=0;j<N;j++){
			cout<<record[i][j]<<" "; 
		}
		cout<<endl; 
	}
	cout<<endl;
	print(record,0,N-1);
	return 0;
} 


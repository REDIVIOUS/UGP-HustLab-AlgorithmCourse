#include <iostream>
#include <utility>
#define INF 100000
using namespace std;

int N;
int opt[1000][1000], record[1000][1000]; //opt：最优解矩阵，record：用于记录括号位置
pair<int, int> p0[1000]; //记录每个矩阵的大小
int p[1000]; //存储矩阵大小序列

void opt_generate(int p[1000], int opt[1000][1000], int record[1000][1000], int N){
	for(int i=0;i<N;i++){
		opt[i][i]=0; //对角线开销置0 
	}
	for(int i=0;i<N;i++){
		record[i][i]=i; //每个元素开始时括号为自己（边界情况，链长为1的情况） 
	} 
	/*构造最优解矩阵*/
	for(int i=2;i<=N;i++){  //i代表当前所处理的矩阵链的长度 
		for(int j=0;j<=N-i;j++){ //j代表当前链开始的横坐标 
			int z=j+i-1; //z代表当前链结束的横坐标 
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
void print(int record[1000][1000], int i,int j){
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
	cin>>N;
	for(int i=0;i<N;i++){
		cin>>p0[i].first;
		cin>>p0[i].second;
	}
	
	//如果输入不合法，汇报错误 
	for(int i=1;i<N;i++){
		if(p0[i].first!=p0[i-1].second){
			cout<<"This matrix can not multiply."<<endl;
			return 0;
		}
	} 
	
	//生成矩阵大小序列 
	for(int i=0;i<N;i++){
		p[i]=p0[i].first; 
	}
	p[N]=p0[N-1].second;
	
	opt_generate(p,opt,record,N);

	cout<<"最少要进行的乘法步骤为："<<opt[0][N-1]<<"次"<<endl; 
	print(record,0,N-1);
	return 0;
} 



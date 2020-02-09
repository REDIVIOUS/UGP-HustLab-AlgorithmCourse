#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int M; //背包总容量
	int n; //物品的件数
	cin>>n>>M;
	
	int w[n+5],p[n+5]; //每件物品的重量w[i],价值p[i]
	int KNAP[n+5][M+5]; //前i件物品装入j容量的最大价值 
	
	for(int i=1;i<=n;i++){ //读入物品重量 
		cin>>w[i];
	}
	for(int i=1;i<=n;i++){ //读入物品价值 
		cin>>p[i];
	}
	
	for(int j=0;j<=M;j++){ //初始化边界条件，前0件商品最大价值为0 
		KNAP[0][j]=0; 
	}
	
	for(int i=1;i<=n;i++){
		for(int j=0;j<=M;j++){
			if(w[i]>j){ //如果背包容量不够第i件商品，则一定不装入 
				KNAP[i][j]=KNAP[i-1][j]; 
			}
			else{  //否则选择是否装第i件物品  
			KNAP[i][j]=max(KNAP[i-1][j],KNAP[i-1][j-w[i]]+p[i]); 
			} 
		} 
	} 

	cout<<"背包能装入的最大价值为："<<KNAP[n][M]; 
	return 0; 
}

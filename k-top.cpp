#include <iostream>
#include <algorithm>
using namespace std;

int GetMid(int a[],int start,int end){ //求出数组a在start到end位置上的中位数的下标 
	sort(a+start,a+end+1); //start到end排序
	int temp=start+end;
	int mid=(temp/2)+(temp%2); //取中位数的下标
	return mid; 
}

int GetMidPivot(int a[],int start, int end){ //将数组a划分，求出中位数的中位数的下标 
	int len=end-start+1;
	int group=len/5+(len%5==0?0:1); //求出组数，不足5个按照5个计算 
	int pivot[group]; //存储每一组中位数的下标 
	for(int k=0;k<group;k++){
		int i=start+k*5,w=i+4,j=min((i+4),end);
		pivot[k]=GetMid(a,i,j); //求出每一组的中位数下标 
	}
	int index=GetMid(pivot,0,group-1); //取中位数下标数组的中位数的下标 
	return pivot[index];
}

void bfqrt(int a[],int left,int right, int k){ //分治主体 
	//挖坑法实现 
	int i=left,j=right;
	int pivot_index=GetMidPivot(a,left,right); //求中位数的中位数的下标
	int pivot=a[pivot_index];
	swap(a[pivot_index],a[right]); //将基准值放在数组末尾 
	while(i<j){
		while(i<j&&a[i]<=pivot){ //左边开始寻找比pivot大的数进行交换 
			i++; 
		}
		a[j]=a[i];
		while(i<j&&a[j]>=pivot){ //右边开始寻找比pivot小的数进行交换 
			j--;
		}
		a[i]=a[j];
	}
	a[i]=pivot;
	if(i>k-1){
		bfqrt(a,left,i-1,k); //在左边继续搜索 
	}
	else if(i<k-1){
		bfqrt(a,i+1,right,k); //在右边继续搜索 
	}
	else{
		cout<<"The k-smallest number is: "<<a[i]<<endl;
		return ;
	}
} 

int main(){
	int k,n;  //要寻找的序号k,数组长度n
	cin>>k>>n;  //读入序号k，长度n 
	int a[n]; //要查找的数组a
	for(int i=0;i<n;i++){ //读入数组a[]
		cin>>a[i]; 
	}
	if(k>n){ //若要寻找的需要大于数组大小，报错 
		cout<<"the k-smallest number does not exist!"<<endl;
		return 0;
	}
	bfqrt(a,0,n-1,k); //调用函数寻找第k小的数
	return 0;
}

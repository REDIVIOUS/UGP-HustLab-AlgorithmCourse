#include <iostream>
using namespace std;

void k_smallest(int a[], int left, int right, int k){ //left和right分别为当前查询数组的下界和上界，查询第k小的元素 
	//挖坑法实现 
	int i=left,j=right;
	int pivot=a[j]; //第一个坑设置为最后一个元素 
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
	a[i]=pivot; //pivot填入 
	if(i>k-1){
		k_smallest(a,left,i-1,k); //在左边继续搜索 
	}
	else if(i<k-1){
		k_smallest(a,i+1,right,k); //在右边继续搜索  
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
	k_smallest(a,0,n-1,k); //调用函数寻找第k小的数
	return 0;
} 

#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;


struct node{
	int val;
	struct node* ptr;
};
int count=1000;
int main(){
	node * head;
	while(--count){
		head=new node;
		head->val=100+count;
		head->ptr=nullptr;
		cout<<"the header val"<<head->val<<endl;
		sleep(10);
	}
}

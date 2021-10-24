#include<stdio.h>
#include<iostream>
#include<string.h>
#include <unordered_map>
#include<map>

using namespace std;
typedef struct Dequeue dequeue;

struct Dequeue
{
	dequeue *prev;
	dequeue *next;
	int data;
	int key; // need to erase element in O(1)
};

class LRUCache
{

	int capacity=0;
	int length=0;
	unordered_map<int ,dequeue*> keyMap;

 public:
 	dequeue *front=NULL;
	dequeue *back=NULL;

	void printCache()
	{	
		cout<<"============================="<<endl;
		dequeue *tmp=front;
		if(!tmp)
			cout<<"cache empty or Size <=0";

		while(tmp!=NULL)
				{
					cout<<tmp->key<<"-"<<tmp->data<<" ";
					tmp=tmp->next;
				}
				cout<<endl;

		cout<<"============================="<<endl;
	}

	LRUCache(int size)
	{
		capacity=size;
	}
	int get_capacity()
	{
		return capacity;
	}
	void pop_back()//get back pointer
	{
		if(front==back)
		{
			free(back);
			front=NULL;
			back=NULL;
			return;
		}
		dequeue *lastNode=back->prev;
		
		if(lastNode!=NULL)
			lastNode->next=NULL;
		else
			front=NULL;

		free(back);
		back=lastNode;	
	}
	void push_front(int key,int data)
	{
		dequeue *newNode= (dequeue *)malloc(sizeof(dequeue));
		newNode->data=data;
		newNode->key=key;
		newNode->next=front;
		if(front!=NULL)
			front->prev=newNode;
	
		front=newNode;
		if(back==NULL)
			back=front;
	}
	
	void rearrange(dequeue *node)//ptr to node given
	{
		if(front==back)
		{
			return;
		}

		if(node == back)// || node->next==NULL
		{	
			dequeue *lastNode=node->prev;
			lastNode->next=NULL;

			node->next=front;
			node->prev=NULL;
			node->next->prev=node;
			front=node;
			back=lastNode;
		}
		else if(node == front)//node == front || node->prev==NULL
		{   
			return; //already at the begining 
		}
		else
		{
			dequeue *lastNode=node->prev;
			lastNode->next=node->next;
			lastNode->next->prev=lastNode;

			node->next=front;
			node->next->prev=node;
			front=node;
		}
	}
	int get(int key)
	{
		if(capacity<=0)
			return -1;
	
		if(keyMap.find(key)!=keyMap.end())//key found 
		{

			rearrange(keyMap[key]); //get 
			return keyMap[key]->data;
		}
		return -1;
	}

	void set(int key,int val)
	{

		if(capacity<=0)
			return;

		if(keyMap.find(key)!=keyMap.end())//got key in map
		{
			rearrange(keyMap[key]);
			keyMap[key]->data=val;//updated the key
		}
		else
		{
			//key not found we will check for size 
			//if less than capacity insert node else remove node and insert
			if(length==0)
			{
				push_front(key,val);
				back=front;
				keyMap[key]=front;
				length++;
			}
			else if(length==capacity)
			{
				keyMap.erase(back->key);
				pop_back();
				push_front(key,val);
				keyMap[key]=front;	
			}
			else
			{
				push_front(key,val);
				keyMap[key]=front;
				length++;
			}


		}
	}
	

};





int main()
{
<<<<<<< HEAD
	

	int cap=0,q=0;
	int num=0,key=0,val=0;

	cin>>cap>>q;
	LRUCache l1(cap);

	while(q--)
	{
		cin>>num;

		if(num==1)
		{
			cin>>key;
			cout<<l1.get(key)<<endl;
		}
		else
		{
			cin>>key>>val;
			l1.set(key,val);
		}

	}
	/*
=======
	LRUCache l1(3);

>>>>>>> c959ee2d750d69eaa55b39abe42a674527c2d501
	l1.set(1,1);
	l1.printCache();
	l1.set(2,2);
	l1.printCache();
	l1.set(3,3);
	l1.printCache();
	l1.set(4,4);
	l1.printCache();
	l1.get(4);
	l1.printCache();
	l1.get(3);
	l1.printCache();
	l1.get(2);
	l1.printCache();
	l1.get(1);
	l1.printCache();
	l1.set(5,5);
	l1.printCache();
	l1.get(1);
	l1.printCache();
	l1.get(2);
	l1.printCache();
	l1.get(3);
	l1.printCache();
	l1.get(4);
	l1.printCache();
	l1.get(5);
	l1.printCache();
<<<<<<< HEAD
*/
=======

>>>>>>> c959ee2d750d69eaa55b39abe42a674527c2d501
	return 0;
}






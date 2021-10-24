#include<stdio.h>
#include<iostream>
#include<string.h>
#include<unordered_map>
#include<map>


using namespace std;
typedef struct Dequeue dequeue;
typedef struct Pair mpair;

struct Dequeue
{
	dequeue *prev;
	dequeue *next;
	int data;
	int key; // while deleting key in case of overflow
};

struct Pair
{
	dequeue *front;
	dequeue *back;
};


class LFUCache
{

	int capacity=0;
	int length=0;
	int least_freq=0;
	unordered_map<int ,dequeue*> keyMap;
	unordered_map<int ,int> freqMap;//key=>freq
	map<int ,mpair > pairMap;//freq=>list of nodes

 public:
 	//dequeue *front=NULL;
	//dequeue *back=NULL;
	
	void printCache()
	{
		for(auto it=pairMap.begin();it!=pairMap.end();it++)
		{

			mpair p =it->second;

			cout<<it->first<<"::";
			dequeue *tmp=p.front;
			if(!tmp)
				cout<<"Key empty";

			while(tmp!=NULL)
					{
						cout<<tmp->key<<"-"<<tmp->data<<" ";
						tmp=tmp->next;
					}
					cout<<endl;
		}
		cout<<"-----------------------"<<endl;
		
	}

	LFUCache(int size)
	{
		capacity=size;
		least_freq=0;}

	int get_capacity()
	{return capacity;}


	int get(int key)
	{
		if(capacity<=0)
			return -1;

		if(keyMap.find(key)!=keyMap.end())
		{
			removeKey(key);		
			freqMap[key]++;
			insertKey(pairMap[  freqMap[key] ],keyMap[key]);

			return keyMap[key]->data;
		}
		return -1;
	}

	/*void removeKey(mpair &p,dequeue *node)
	{
		
		if(p.front==p.back)
		{
			p.front=NULL;
			p.back=NULL;
		}
		else if(p.front == node)
		{
			p.front=p.front->next;
		}
		else if(p.back == node )
		{
			p.back=p.back->prev; 
		}
		else
		{
			node->prev->next=node->next;
			node->next->prev=node->prev;
		}
	}*/

	void removeKey(int k)
	{
		
		dequeue *node= keyMap[k];
		mpair p = pairMap[ freqMap[k] ];
		int freq=freqMap[k];
		if(p.front==p.back)
		{
			p.front=NULL;
			p.back=NULL;
			
		}
		else if(p.front == node)
		{
			p.front=p.front->next;
		}
		else if(p.back == node )
		{
			p.back=p.back->prev;
			p.back->next=NULL; 
		}
		else
		{
			node->prev->next=node->next;
			node->next->prev=node->prev;
		}

		pairMap[ freqMap[k] ] = p;

		if(p.front ==NULL)
			pairMap.erase(freq);

	}

	void insertKey(mpair &p,dequeue *node)
	{
		node->next=NULL;
		node->prev=NULL;

		if(p.front==NULL && p.back==NULL)
		{
			p.front=node;
		}
		else
		{
			p.back->next=node;
			node->prev=p.back;		
		}
		p.back=node;
	}

	void set(int key,int val)
	{
		
		
		if(keyMap.find(key)!=keyMap.end())//found the key
		{
			//update key value
			//remove key from pairMap
			//increase frequency

			keyMap[key]->data=val;
			//removeKey(pairMap[ freqMap[key] ],keyMap[key]);
			removeKey(key);		
			freqMap[key]++;
			insertKey(pairMap[  freqMap[key] ],keyMap[key]);

		}
		else
		{
			dequeue *node=(dequeue*)malloc(sizeof(dequeue));
			node->data=val;
			node->key=key;
			keyMap[key]=node;
			freqMap[key]=1;
			if(length==0)
			{
				insertKey(pairMap[  freqMap[key] ],keyMap[key]);
				length++;
			}
			else if(length==capacity)
			{
				//cout<<"len==capa\n";
				auto it = pairMap.begin();
				//mpair tmp = it->second;
				int nkey = (it->second).front->key;

				//LFU key removed
				//removeKey(pairMap[ freqMap[nkey] ],keyMap[nkey]);
				removeKey(nkey);
				keyMap.erase(nkey);
				freqMap.erase(nkey);

				//insert new keys
				insertKey(pairMap[  freqMap[key] ],keyMap[key]);				

			}
			else
			{
				insertKey(pairMap[  freqMap[key] ],keyMap[key]);				
				length++;				
			}

		}
	}
	

};

int main()
{
	int size=3;
	LFUCache l1(size);
	cout<<l1.get_capacity();
	l1.set(1,10);
	l1.printCache();

	l1.set(3,30);
	l1.printCache();

	l1.set(4,40);
	l1.printCache();	
	cout<<l1.get(1)<<" "<<l1.get(4)<<endl;
	
	l1.set(5,50);
	l1.printCache();	
	
	l1.set(1,40);
	cout<<l1.get(4)<<" "<<l1.get(5)<<endl;
	l1.printCache();	

	l1.set(2,40);
	l1.printCache();	
	
	l1.set(6,60);
	l1.printCache();	
	
	
	
	cout<<l1.get(3)<<endl;
	cout<<l1.get(1)<<endl;
	cout<<l1.get(6)<<endl;
	
	


	return 0;
}



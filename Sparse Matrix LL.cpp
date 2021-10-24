#include<iostream>

using namespace std;

template<typename T>
class Node
{
public:
	int row;
	int col;
	T value;
	Node *next;
};


template<typename T>
Node<T>* getLinkedList(T arr[5][5],int n,int m)
{
	Node<T> *tmp,*head=NULL;

	Node<T> *node=(Node<T> *)malloc(sizeof(Node<T>));
	head=node;
	tmp=head;

	node->row=n;
	node->col=m;
	node->value=0;

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{

			if(arr[i][j]!=0)
			{
				node=(Node<T> *)malloc(sizeof(Node<T>));
				node->row=i;
				node->col=j;
				node->value=arr[i][j];	
				tmp->next=node;
				tmp=tmp->next;				
			}
		}
	}

	return head;
} 


template<typename T>
int myGreater(Node<T> *A, Node<T> *B)
{
	if(A->row < B->row)
	{
		return -1;
	}
	else if(A->row == B->row)
	{
		if(A->col<B->col)
			return -1;
		else if(A->col>B->col)
			return 1;
		else
			return 0;

	}
	else
	{
		return 1;
	}
}

template<typename T>
void sortList(Node<T> *head) {  
    
    Node<T> *current = head, *index = NULL;  
    T temprow,tempcol,tempval;  
      
    if(head == NULL) {  
        return;  
    }  
    else {  
        while(current != NULL) {  
            
            index = current->next;  
              
            while(index != NULL) {  
                
                if(myGreater(current,index)==1) {  
                    
                	temprow=current->row;
                	tempcol=current->col;
                	tempval=current->value;

                	current->row=index->row;
                	current->col=index->col;
                	current->value=index->value;

                    index->row=temprow;
                    index->col=tempcol;
                    index->value=tempval; 
                }  
                index = index->next;  
            }  
            current = current->next;  
        }      
    }  
}

template<typename T>
Node<T>* transposeList(Node<T> *node)
{

	Node<T> *tmp=node;

	while(tmp!=NULL)
	{
		int tmpvar=tmp->row;
		tmp->row=tmp->col;
		tmp->col=tmpvar;

		tmp=tmp->next;
	}

	tmp=node;

	sortList(tmp->next);

	while(tmp!=NULL)
	{
		cout<<tmp->row<<" "<<tmp->col<<" "<<tmp->value<<endl;
		tmp=tmp->next;
	}
	

	return node;

}


template<typename T>
Node<T>* additionList(Node<T> *l1, Node<T> *l2)
{

	if(l1->row!=l2->row || l2->col!=l2->col)
	{
		return NULL;
	}

	Node<T> *tmp,*head=NULL;

	Node<T> *node=(Node<T> *)malloc(sizeof(Node<T>));
	head=node;
	tmp=head;

	node->row=l1->row;
	node->col=l1->col;
	node->value=0;

	l1=l1->next;
	l2=l2->next;

	while(l1 && l2)
	{
		if(myGreater(l1,l2)==0 )
		{
			if((l1->value + l2->value)!=0)
			{
				node=(Node<T> *)malloc(sizeof(Node<T>));
				node->row=l1->row;
				node->col=l1->col;
				node->value = l1->value + l2->value;
				
				tmp->next=node;
				tmp=tmp->next;
			}
			l1=l1->next;
			l2=l2->next;

		}
		else if(myGreater(l1,l2)==1)
		{
			node=(Node<T> *)malloc(sizeof(Node<T>));
			node->row=l2->row;
			node->col=l2->col;
			node->value =l2->value;

			tmp->next=node;
			tmp=tmp->next;

			l2=l2->next;
		}
		else
		{
			node=(Node<T> *)malloc(sizeof(Node<T>));
			node->row=l1->row;
			node->col=l1->col;
			node->value =l1->value;

			tmp->next=node;
			tmp=tmp->next;

			l1=l1->next;
		}

	}
	while(l1)
	{
		node=(Node<T> *)malloc(sizeof(Node<T>));
		node->row=l1->row;
		node->col=l1->col;
		node->value =l1->value;

		tmp->next=node;
		tmp=tmp->next;

		l1=l1->next;

	}
	while(l2)
	{
		node=(Node<T> *)malloc(sizeof(Node<T>));
		node->row=l2->row;
		node->col=l2->col;
		node->value =l2->value;

		tmp->next=node;
		tmp=tmp->next;

		l2=l2->next;

	}

	return head;
} 

template<typename T>
Node<T>* multiplyList(Node<T> *l1, Node<T> *l2)
{

	if(l1->col!=l2->row)
	{
		return NULL;
	}

	Node<T> *tmp,*head=NULL;

	


	Node<T> *node=(Node<T> *)malloc(sizeof(Node<T>));
	tmp=head=node;
	

	node->row=l1->row;
	node->col=l2->col;
	node->value=0;

	l1=l1->next;
	l2=l2->next;

	Node<T> *list1=l1,*list2=l2,*tmp2=NULL;

	while(l1)
	{
		l2=list2;
		while(l2)
		{
			if(l1->col == l2->row)
			{
				node=(Node<T> *)malloc(sizeof(Node<T>));
				node->row=l1->row;
				node->col=l2->col;
				node->value = l1->value * l2->value;
				
				tmp->next=node;
				tmp=tmp->next;
			}

		l2=l2->next;
		}

		l1=l1->next;
	}

	tmp=head;

	while(tmp!=NULL)
	{	
		cout<<tmp->row<<" "<<tmp->col<<" "<<tmp->value<<endl;
		tmp=tmp->next;
	}

	cout<<"^-----"<<endl;	
	
	tmp=head;
	sortList(tmp->next);
	tmp=head->next;

	Node<T> *lastPtr=head; //new changes



	if(tmp)
		tmp2=tmp->next;
	else
		return head;
	
	T intersum=tmp->value;
	while(tmp2)
	{
		
		if(myGreater(tmp,tmp2)==0)
		{
		   intersum+=tmp2->value;
		   tmp->next=tmp2->next;	
		   free(tmp2);
		   tmp2=tmp->next;
		}
		else
		{	
			if(intersum!=0)
				{tmp->value=intersum;
				 lastPtr=tmp;
				}
			else
			{
				free(tmp);
				lastPtr->next=tmp2;
			}


			tmp=tmp2;
			intersum=tmp->value;

			if(tmp2)
				tmp2=tmp2->next;

		}

	}

	return head;
} 




int main()
{

	//float arr[5][5]={{1.5,2.5,3.2,4.123,1.0},{2,0,0,3,0},{0,0,0,0,0},{1,2,3,0,0},{0,0,10,0,0}};
	//float arr1[5][5]={{2,2,2,2,1},{6,0,0,3,0},{0,1,0,0,0},{0,0,3,0,0},{0,0,-10,0,0}};
	Node<float> *head;

	//head=getLinkedList<float>(arr,5,5);

	Node<int> *tmp;
	/*

	tmp=node;
	while(tmp!=NULL)
	{	
		cout<<tmp->row<<" "<<tmp->col<<" "<<tmp->value<<endl;
		tmp=tmp->next;
	}

	cout<<endl;
	//thead=transposeList<float>(head);

*/
	/*
	tmp=getLinkedList(arr1,5,5);
	while(tmp!=NULL)
	{	
		cout<<tmp->row<<" "<<tmp->col<<" "<<tmp->value<<endl;
		tmp=tmp->next;
	}
	*/
<<<<<<< HEAD
	int arr[5][5]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
	int arr1[5][5]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
=======
	int arr[5][5]={{1,0,0,0,0},{0,1,0,0,0},{0,0,1,0,0},{0,0,0,0,0},{0,0,0,0,0}};
	int arr1[5][5]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,1,0},{0,0,0,0,1}};
>>>>>>> c959ee2d750d69eaa55b39abe42a674527c2d501


	tmp=multiplyList(getLinkedList(arr,5,5),getLinkedList(arr1,5,5));
	
	while(tmp!=NULL)
	{	
		cout<<tmp->row<<" "<<tmp->col<<" "<<tmp->value<<endl;
		tmp=tmp->next;
	}

	return 0;



}




#include<iostream>
#include<stdio.h>
using namespace std;
struct node
{
	int key;
	struct node* next;
      //void push(int key);
};
/*void node::push(int key)
{
	if (this == NULL)
	{
		printf("Memory is not allocated");
		struct node* temp = new node;
		this=temp;
		//this =new node;
		this->key=key;
		this->next=NULL;
	}	
}*/
void push(struct node** list,int key)
{
	if (*list == NULL)
	{
		*list=new node;
		(*list)->key=key;
		(*list)->next=NULL;
	}
	else
		push(&(*list)->next,key);
}
void print(struct node* list)
{
	while (list != NULL)
	{
		printf("%d ",list->key);
		list=list->next;
	}

	cout<<endl;
}
int count(struct node* list,int key)
{
	int c=0;
	
	for(;list != NULL;list=list->next)
	{
		if (list->key == key)
			c++;
	}
	
	return c;
}
int GetNth(struct node* list,int index)
{
	int key=0;
	int count=0;
	
	for (;list != NULL;list=list->next)
	{
		if (count == index)
			return list->key;
		
		count++;
	}

	return -1;
}
void delete_list(struct node** list)
{
	if (*list == NULL)
		return;
	
	delete_list(&(*list)->next);
	
	printf("Deleting the key [%d] \n",(*list)->key);
	delete *list;
	*list=NULL;
	
	return;
}
void pop(struct node** list)
{
	if (*list == NULL)
		return;
	
	struct node* temp=*list;
	
	*list=(*list)->next;
	
	printf("Poping the key [%d] \n",temp->key);
	
	delete temp;
	temp=NULL;
}
int Get_Length(struct node* list)
{
	if (list == NULL)
		return 0;
	
	int count=0;
	
	while (list != NULL)
	{
		count++;
		list=list->next;
	}

	return count;
}	
bool InsertNth(struct node** list,int index,int key)
{
	if (*list == NULL)
		return false;
	
	
	int length=Get_Length(*list);
	
	printf("Length is [%d] \n",length);
	
	if (index > length)
		return false;
	
	if (index == 0)
	{
		struct node* temp=new node;
		temp->key=key;
		temp->next=*list;
		*list=temp;
		
		return true;
	}	
	
	if (index == length)
	{
		push(list,key);
		return true;
	}	
	
	struct node* f=*list;
	struct node* n=(*list)->next;
	int count=1;
	
	while (n != NULL)
	{
		if (count == index)
		{
			struct node* temp=new node;
			temp->key=key;
			temp->next=n;
			f->next=temp;
			
			return true;
		}
		
		count++;
		f=f->next;
		n=n->next;
	}	
	
	return false;
}
void SortedInsert(struct node** head,struct node* newNode)
{
	if (*head == NULL)
	{
		newNode->next=*head;
		*head=newNode;
		return;
	}	
	
	if ((*head)->key >= newNode->key)
	{
		struct node* t=*head;
		*head=newNode;
		newNode->next=t;
		return;
	}
	
	struct node* temp=*head;
	struct node* n=(*head)->next;
	
	while (n != NULL)
	{
		if (n->key >= newNode->key)
		{
			temp->next=newNode;
			newNode->next=n;
			return;
		}

		temp=temp->next;
		n=n->next;
	}

	temp->next=newNode;
	newNode->next=n;
	return;
}
void Insertsort(struct node** head)
{
	if (*head == NULL || (*head)->next == NULL)
		return;
	
	struct node* result=NULL;
	struct node* current=*head;
	struct node* n;
	
	while (current != NULL)
	{
		n=current->next;
		SortedInsert(&result,current);
		current=n;
	}	
	
	*head=result;
	return;
}
void Append(struct node** a,struct node** b)
{
	if (*b == NULL)
		return;
	
	if (*a == NULL)
	{
		*a=*b;
		*b=NULL;
	}
	else
	{
		struct node* temp=*a;
		
		while (temp->next != NULL)
			temp=temp->next;
		
		
		temp->next=*b;
		*b=NULL;
	}
	
	return;
}
void FrontBackSpilt(struct node* source,struct node** front,struct node** back)
{
	if (source == NULL)
		return;
	
	if (source->next == NULL)
	{
		*front=source;
		return;
	}	
	
	struct node* slow=source;
	
	struct node* fast=source->next;
	
	while (fast != NULL)
	{
		if (fast->next != NULL)
		{
			slow=slow->next;
			fast=fast->next->next;
		}	
		else
			fast=fast->next;
	}

	*front=source;
	*back=slow->next;
	slow->next=NULL;
}
void RemoveDuplicates(struct node** head)
{
	if (*head == NULL || (*head)->next == NULL)
		return;
	
	struct node* temp=*head;
	
	while (*head != NULL && (*head)->next != NULL)
	{
		if ((*head)->key == (*head)->next->key)
		{
			struct node* t=(*head)->next;
			(*head)->next=t->next;
			delete t;
			t=NULL;
		}
		else
			*head=(*head)->next;
	}	
	
	*head=temp;
	return;
}
void Movenode(struct node** src,struct node** dest)
{
	if (*src == NULL)
		return;
	
	struct node* temp=*src;
	*src=(*src)->next;
	
	temp->next=*dest;
	*dest=temp;
	
	return;
}
void AlternateSplit(struct node* source,struct node** f,struct node** s)
{
	if (source == NULL)
		return;
	
	while (source != NULL)
	{
		Movenode(&source,f);
		Movenode(&source,s);
	}	
}
struct node* ShuffleMerge(struct node* a,struct node* b)
{
	struct node* result;
	struct node* recur;
	
	
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	else
	{
		recur=ShuffleMerge(a->next,b->next);
		
		result=a;
		a->next=b;
		b->next=recur;
		
		return result;
	}	
	
}
struct node* SortedMerge(struct node* a,struct node* b)
{
	struct node* ref=NULL;
	struct node* recur=NULL;
	
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
        else
	{
		if (a->key < b->key)
		{
			ref=a;
			recur=SortedMerge(a->next,b);
		}
		else
		{
			ref=b;
			recur=SortedMerge(a,b->next);
		}
		
		ref->next=recur;
	}

	return ref;
}
struct node* SortedMerge_2(struct node* a,struct node* b)
{
	struct node* result=NULL;
	struct node** ref=&result;
	while(1)
	{
		if (a == NULL)
		{
			*ref=b;
			break;
		}
		else if (b == NULL)
		{
			*ref=a;
			break;
		}
		
		if (a->key < b->key)
		{
			Movenode(&a,ref);
		}
		else
		{
			Movenode(&b,ref);
		}	
		
		ref=&((*ref)->next);
        }	
	
	return result;
}
void Merge_Sort(struct node** headref)
{
	
	//cout<<"Get length is : "<<Get_Length(head)<<endl;
	
	struct node* head=*headref;
	
	if (head->next == NULL)
		return;
	
	struct node* f=NULL;
	struct node* b=NULL;
	
	FrontBackSpilt(head,&f,&b);
	
	Merge_Sort(&f);
	
	Merge_Sort(&b);
	
	*headref=SortedMerge(f,b);
	
}
struct node* SortedIntersect(struct node* a,struct node* b)
{
	if (a == NULL || b == NULL)
		return NULL;
	
	struct node* result=NULL;
	struct node** ref=&result;
	
	while(1)
	{
		if (a == NULL || b == NULL)
			break;
		
		if (a->key == b->key)
		{
			push(ref,a->key);
			a=a->next;
			b=b->next;
			ref=&((*ref)->next);
			continue;
		}
		
		if (a->key < b->key)
			a=a->next;
		else
			b=b->next;
        }

	return result;
}
void Reverse(struct node** a)
{
	if (*a == NULL)
		return;
	
	struct node* result=NULL;
	struct node** ref=&result;
	
	while (*a != NULL)
		Movenode(a,ref);
	
	*a=result;
}
void RecursiveReverse(struct node** a)
{
	if (*a == NULL)
		return;
	
	struct node* first=*a;
	struct node* rest=(*a)->next;
	
	if (rest == NULL)
		return;
	
	RecursiveReverse(&rest);
	
	first->next->next=first;
	first->next=NULL;
	
	*a=rest;
}	
int main()
{
	struct node* list=NULL;
	push(&list,15);
	push(&list,14);
	push(&list,13);
	push(&list,12);
	
	print(list);
	
	printf("Total count of [%d] in the list is : [%d] \n",12,count(list,12));
	
	printf("Node [%d] is at the index [%d] \n",GetNth(list,3),3);
	
	//delete_list(&list);
	
	if (list == NULL)
		printf("List is successfully deleted \n");
	else
		printf("List is not deleted \n");
	
	//pop(&list);
	
	InsertNth(&list,1,11);
	print(list);
	
	struct node* temp=NULL;
	push(&temp,9);
	
	//SortedInsert(&list,temp);
	
	Insertsort(&list);
	print(list);
	
	struct node* a=NULL;
	Append(&a,&list);
	
	struct node* b=NULL;
	push(&b,15);
	push(&b,14);
	push(&b,13);
	push(&b,12);
	
	Append(&a,&b);
	
	Insertsort(&a);
	
	pop(&a);
	print(a);
	
	struct node* front=NULL;
	struct node* back=NULL;
	
	struct node* c=NULL;
	push(&c,15);
	push(&c,14);
	push(&c,8);
	
	/*FrontBackSpilt(a,&front,&back);
	print(front);
	RemoveDuplicates(&front);
	RemoveDuplicates(&back);
	print(front);
	print(back);*/
	
	RemoveDuplicates(&a);
	
	Movenode(&a,&c);
	print(a);
	print(c);
	
	struct node* f=NULL;
	struct node* s=NULL;
	
	AlternateSplit(c,&f,&s);
	
	push(&f,19);
	push(&f,27);
	push(&s,23);
	push(&s,34);
	
	Insertsort(&f);
	print(f);
	print(s);
		
	//struct node* ref=ShuffleMerge(f,s);
	struct node* ref=SortedMerge_2(f,s);
	print(ref);
	
	struct node* m=NULL;
	push(&m,15);
	push(&m,14);
	push(&m,13);
	push(&m,12);
	push(&m,11);
	
	Merge_Sort(&m);
	print(m);
	
	struct node* inter=SortedIntersect(ref,m);
	print(inter);
	
	Reverse(&ref);
	print(ref);
	
	RecursiveReverse(&ref);
	print(ref);
}	

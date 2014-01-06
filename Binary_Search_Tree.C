#include<iostream>
#include<stdio.h>
#include<queue>
#include<limits.h>
using namespace std;
struct node
{
	int key;
	struct node* left;
	struct node* right;
};
void insert(struct node** t,int key)
{
	if (*t == NULL)
	{
		*t=new node;
		(*t)->key=key;
		(*t)->left=NULL;
		(*t)->right=NULL;
	}
	else if (key < (*t)->key)
		insert(&(*t)->left,key);
	else
		insert(&(*t)->right,key);
	
}
void print_levelorder(struct node* t)
{
	queue<struct node*> q;
	q.push(t);
	
	while (!q.empty())
	{
		if (q.front() != NULL)
		{
			printf("%d ",q.front()->key);
			
			q.push(q.front()->left != NULL  ? q.front()->left:NULL);
			q.push(q.front()->right != NULL ? q.front()->right:NULL);
		}	
		
		q.pop();
	}	
	
	cout<<endl;
}
void print_Inorder(struct node* t)//In-order prints the tree in ascending order
{
	if (t == NULL)
		return;
	
	print_Inorder(t->left);
	printf("%d ",t->key);
	print_Inorder(t->right);
}
int size(struct node* t)
{
	if (t == NULL)
		return 0;
	else
		return 1+size(t->left)+size(t->right);
}
int maxdepth(struct node* t)
{
	if (t == NULL)
		return 0;
	else
		return max(1+maxdepth(t->left),1+maxdepth(t->right));
}
int min_value(struct node* t)
{
	if (t == NULL)
		return -1;
	
	if (t->left != NULL)
		return min_value(t->left);
	else
		return t->key;
}
int max_value(struct node* t)
{
	if (t == NULL)
		return -1;
	
	if (t->right != NULL)
		return max_value(t->right);
	else
		return t->key;
}
bool HasPathSum(struct node* t,int sum)
{
	if (t == NULL && sum == 0)
		return true;
	
	if (t == NULL || t->key > sum)
		return false;
	
	
	return HasPathSum(t->left,sum - t->key) || HasPathSum(t->right,sum - t->key);
	
}
void printPaths(struct node* t,int R[],int pathlen)
{
	if (t == NULL)
	{
		return;
	}

	R[pathlen]=t->key;
	
	if (t->left == NULL && t->right == NULL)//End of the path (Reached leaf node)
	{
		for(int i=0;i<=pathlen;i++)
		{
			printf("%d ",R[i]);
		}	
		cout<<endl;
	}	
	else
	{
		printPaths(t->left,R,pathlen+1);
		printPaths(t->right,R,pathlen+1);
	}	
}
void Mirror(struct node* source,struct node** dest)
{
	if (source == NULL)
		return;
	
	insert(dest,source->key);
	Mirror(source->left,&(*dest)->right);
	Mirror(source->right,&(*dest)->left);
}
int countrees(int numkeys)
{
	if (numkeys <= 1)//One or less node has 1 BST
		return 1;
	
	int sum=0;
	int left,right=0;
	
	for (int root=1;root<=numkeys;root++)
	{
		left=countrees(root-1);//Number of different sub-trees can be formed with left side
		right=countrees(numkeys-root);//Number of different sub-trees can be formed with right side
		
		sum=sum+(left*right);//Recursively sum it up
	}

	return sum;
}
bool Is_BST_Recur(struct node*t,int min,int max)
{
	if (t == NULL)
		return true;
	
	if (t->key < min || t->key > max)
	{
		printf("Key [%d] is not in the range of [%d] to [%d] \n",t->key,min,max);
		return false;
	}	
	
	return Is_BST_Recur(t->left,min,t->key-1) && Is_BST_Recur(t->right,t->key+1,max);//Slides the range from the given root
}	
bool Is_BST_V1(struct node* t)
{
	if (t == NULL)
		return true;
	
	return Is_BST_Recur(t,INT_MIN,INT_MAX);
}
bool Is_BST_V2(struct node* t)
{
	if (t == NULL)
		return true;
	
	int min=min_value(t);
	int max=max_value(t);
	
	if (t->key < min || t->key > max)
	{
		printf("Key [%d] may be less than minimum value [%d] or greater than maximum value [%d] \n",t->key,min,max);
		return false;
	}	
	
	return Is_BST_V2(t->left) && Is_BST_V2(t->right);
}	
int main()
{
	struct node* t=NULL;
	insert(&t,15);
	insert(&t,10);
	insert(&t,20);
	insert(&t,8);
	insert(&t,12);
	insert(&t,9);
	insert(&t,19);
	
	printf("Level order traversal or BFS is : \n");
	print_levelorder(t);
	
	printf("Inorder traversal is : \n");
	
	print_Inorder(t);
	
	cout<<endl;
	
	printf("Size of tree is : %d \n",size(t));
	
	insert(&t,7);
	insert(&t,6);
	
	printf("Maxium depth of tree is : %d \n",maxdepth(t));
	
	printf("Minimum value of tree is : %d \n",min_value(t));
	
	int sum=38;
	
	if(HasPathSum(t,sum))
		printf("Tree has the path for given value : %d \n",sum);
	else
		printf("Tree does not have the path for give sum \n");
	
	int depth=maxdepth(t);
	
	int R[depth];
	
	printPaths(t,R,0);
	
	struct node* d=NULL;
	
	Mirror(t,&d);
	
	printf("Source tree is : \n");
	print_levelorder(t);
	printf("Mirrored tree is : \n");
	print_levelorder(d);
	
	int c=3;
	printf("[%d] different trees can be formed with [%d] nodes \n",countrees(c),c);
	
	insert(&(t->right->right),18);
	
	if (Is_BST_V2(t))
		printf("Tree is a BST \n");
	else
		printf("Tree is not a BST \n");
	
}	

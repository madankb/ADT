/****************************************************************************************************************************************************************************************
BST :- BST is a abstract data type which has the left key node lesser than root node key and right key node greater than root node.

Depth first search :-
                1) In-order traversal
                2) Pre-order traversal
                3) Post-order traversal	
		
Breadth first search :-
                Visiting all the nodes in the order of level until it finishes the complete height.

Deleting node in BST :-
                1) Leaf node can be deleted directly.
		2) Node with one children is replaced with the key of children key and the children node is send for deletion.
		3) Node with two children can be deleted by replacing with in-order successor (Or) in-order predessor and corresponding successor or predessor is delted then.
		
In-order successor :- Left most node of right side of the tree which is the perfect node to replace the current node and still maintain the grammar of the BST. Largest key in the left tree.

In-order predecessor :- Right most node of left side of the tree which is the perfect node to replace the current node and still maintain the grammar of the BST. Smallest key in thr right tree.

Why do we need AVL?.
       In BST, insert and find operation can be O(n) in worst case. For example:- Inserted in the order of 10,11,12,13,14,15. Now the height of the tree is n which is 6.So find and 
       insert operation would take O(n). To avoid this, tree is height balanced by doing the rotations. Such self-balancing tree is AVL tree. So search and insert operation is always
       O(log n) in AVL.
       
BST :- Insert,Delete and search operation is O(log n) for average case and O(n) for worst case.

AVL :- Insert,Delete and search operation is always O(log n) for both average and worst case.

Where to use AVL?.
      If the operation is more and more of search than insert and delete, then AVL tree is the best tree implementation. Because insert and delete may take too many rotations.
      
Morris traversal:-
        Morris traversal is a in-order tree traversal without recursion and stack. It is traversed by creating in-order predecessor for every node except leaf node because most leaf
        nodes are in-order predecessor of all non-leaves node.	
******************************************************************************************************************************************************************************************/
#include<iostream>
#include<stdio.h>
using namespace std;
struct tree
{
	int key;
	struct tree* left;
	struct tree* right;
};
void insert(struct tree** t,int key)
{
	if (*t == NULL)
	{
		*t=new tree;
		(*t)->key=key;
		(*t)->left=NULL;
		(*t)->right=NULL;
	}
	else if (key > (*t)->key)
		insert(&(*t)->right,key);
	else
		insert(&(*t)->left,key);
}
void print_preorder(struct tree* t)//Root - left -right
{
	if (t == NULL)
		return;
	else
	{
		printf("%d \n",t->key);
		print_preorder(t->left);
		print_preorder(t->right);
	}
}
void print_inorder(struct tree* t) //Left-Root-Right (Sorted keys)
{
	if (t == NULL)
		return;
	else
	{
		print_inorder(t->left);
		printf("%d \n",t->key);
		print_inorder(t->right);
	}
}
void print_postorder(struct tree* t)//left-right-root
{
	if (t==NULL)
		return;
	else
	{
		print_postorder(t->left);
		print_postorder(t->right);
		printf("%d \n",t->key);
	}
}
int Inorder_successor(struct tree* t)
{
	if (t==NULL)
		return -1;
	else if(t->left == NULL)
		return t->key;
	else
		Inorder_successor(t->left);
}
int Inorder_predessor(struct tree* t)
{
	if (t==NULL)
		return -1;
	else if(t->right == NULL)
		return t->key;
	else
		Inorder_predessor(t->right);
}
struct tree* delete_node(struct tree* t,int key)
{
	if (key < t->key)
		t->left=delete_node(t->left,key);
	else if (key > t->key)
		t->right=delete_node(t->right,key);
	else
	{
		if (t->left == NULL && t->right == NULL) //Deleting leaf node
		{
			printf("Deleting leaf node [%d] \n",t->key);
			delete t;
			t=NULL;
			return NULL;
		}
		else if (t->left == NULL) //Deleting node with one left node is null
		{
			printf("Replacing right node [%d] with the node to be deleted [%d] \n",t->right->key,t->key);
			t->key=t->right->key;
			t->right=delete_node(t->right,t->right->key);
		}
		else if (t->right == NULL) //Deleting node with one right node is null
		{
			printf("Replacing left node [%d] with the node to be deleted [%d] \n",t->left->key,t->key);
			t->key=t->left->key;
			t->left=delete_node(t->left,t->left->key);
		}
		else
		{
			int successor=Inorder_successor(t->right);
			printf("Deleting node [%d] with two children by replacing with the inorder-successor [%d] \n",t->key,successor);
			t->key=successor;
			delete_node(t->right,successor);
		}	
	}	
		
}
int height(struct tree* t)
{
	if (t == NULL)
		return 0;
	else
		return max(1+height(t->left),1+height(t->right));
}
void print_BFS(struct tree* t,int level)
{
	if (t == NULL)
		return;
	
	if (level == 1)
		printf("%d ",t->key);
	else
	{
		print_BFS(t->left,level-1);
		print_BFS(t->right,level-1);
	}
}
void print_levelorder(struct tree* t,int height)
{
	for (int i=1;i<=height;i++)
	{
		print_BFS(t,i);
	}
	cout<<endl;
}
void left_rotation(struct tree** t)
{
	if (*t == NULL)
		return;
	else
	{
		struct tree* temp=(*t)->right->left;
		struct tree* root=(*t)->right;
		(*t)->right->left=(*t);
		(*t)->right=temp;
		*t=root;
	}
}	
void right_rotation(struct tree** t)
{
	if (*t == NULL)
		return;
	else
	{
		struct tree* root=(*t)->left;
		struct tree* temp=(*t)->left->right;
		
		(*t)->left->right=(*t);
		(*t)->left=temp;
		(*t)=root;
	}
}
void insert_AVL(struct tree** t,int key)
{
	if (*t == NULL)
	{
		*t=new tree;
		(*t)->key=key;
		(*t)->left=NULL;
		(*t)->right=NULL;
	}
	else if(key < (*t)->key)
		insert_AVL(&(*t)->left,key);
	else
		insert_AVL(&(*t)->right,key);
	
	int l_height=height((*t)->left);
	
	int r_height=height((*t)->right);
	
	int balance=l_height-r_height;
	
	if (balance < -1 && (*t)->right->right != NULL) //Right-right case
		left_rotation(t);
	else if (balance > 1 && (*t)->left->left != NULL) //Left-left case
		right_rotation(t);
	else if (balance < -1 && (*t)->right->left != NULL) //Right-left case
	{
		right_rotation(&(*t)->right);
		left_rotation(t);
	}
	else if (balance > 1 && (*t)->left->right != NULL)//Left-right case
	{
		left_rotation(&(*t)->left);
		right_rotation(t);
	}	
}	
void delete_AVL(struct tree** t,int key)
{
	if (*t == NULL)
		return;
	else if (key < (*t)->key)
		delete_AVL(&(*t)->left,key);
	else if (key > (*t)->key)
		delete_AVL(&(*t)->right,key);
	else
	{
		if ((*t)->left == NULL && (*t)->right == NULL) //Deleting leaf node
		{
			delete *t;
			*t=NULL;
		}
		else if((*t)->right == NULL)//Deleting node with one children
		{
			(*t)->key=(*t)->left->key;
			delete_AVL(&(*t)->left,(*t)->key);
		}
		else if((*t)->left == NULL)//Deleting node with one children
		{
			(*t)->key=(*t)->right->key;
			delete_AVL(&(*t)->right,(*t)->key);
		}
		else//Deleting node with two children
		{
			int in_predecessor=Inorder_predessor((*t)->left);
			(*t)->key=in_predecessor;
			delete_AVL(&(*t)->left,in_predecessor);
		}	
	}
	
	if (*t != NULL)
	{
		int l_height=height((*t)->left);
		
		int r_height=height((*t)->right);
		
		int balance=l_height-r_height;
		
		if (balance < -1 && (*t)->right->right != NULL) //Right-right case
			left_rotation(t);
		else if (balance > 1 && (*t)->left->left != NULL) //Left-left case
			right_rotation(t);
		else if (balance < -1 && (*t)->right->left != NULL) //Right-left case
		{
			right_rotation(&(*t)->right);
			left_rotation(t);
		}
		else if (balance > 1 && (*t)->left->right != NULL)//Left-right case
		{
			left_rotation(&(*t)->left);
			right_rotation(t);
		}
	}	
}
void morris_traversal(struct tree* t)
{
	if (t == NULL)
		return;
	
	struct tree* cur=t;
	
	while (cur != NULL)
	{
		if (cur->left == NULL)
		{
			printf("%d \n",cur->key);//Print leaf node or root node
			cur=cur->right;//Got to right node or predecessor node pointer.
		}
		else
		{
			struct tree* pre=cur->left;
			
			while (pre->right != NULL && pre->right != cur)//Iterate until the predecessor node is found.
				pre=pre->right;
			
			if (pre->right == NULL)//Reached leaf node.
			{
				pre->right=cur;//Make this in-order predecessor to point to his parent node.
				cur=cur->left;//Go to find the in-order predecessor for next node.
			}
			else
			{
				pre->right=NULL;//Revert bank the link created for in-order predecessor
				printf("%d \n",cur->key);//print in-order root tree node
				cur=cur->right;//Go to right side of the node
			}	
		}	
	
	}	
}	
int main()
{
	struct tree* t=NULL;
	insert(&t,9);
	insert(&t,8);
	insert(&t,7);
	insert(&t,11);
	insert(&t,5);
	insert(&t,13);
	
	printf("In-order traversal \n");
	print_inorder(t);
	
	delete_node(t,9);
		
	print_inorder(t);
	
	cout<<"Inorder successor is :"<<Inorder_successor(t->left)<<endl;
	cout<<"Preorder successor is :"<<Inorder_predessor(t->right)<<endl;
	
	insert(&t,14);
	insert(&t,15);
	insert(&t,16);
	
	int h=height(t);
	cout<<"Height of tree is :"<<h<<endl;
	
	left_rotation(&(t->right->right->right));
	
	right_rotation(&(t->left));
	
	print_preorder(t);
	
	struct tree* avl=NULL;
	
	insert_AVL(&avl,10);
	insert_AVL(&avl,11);
	insert_AVL(&avl,12);
	insert_AVL(&avl,13);
	insert_AVL(&avl,19);
	insert_AVL(&avl,22);
	insert_AVL(&avl,9);
	insert_AVL(&avl,8);
	insert_AVL(&avl,21);
	insert_AVL(&avl,5);
	insert_AVL(&avl,7);
	
	delete_AVL(&avl,10);
	delete_AVL(&avl,11);
	delete_AVL(&avl,12);
	//delete_AVL(&avl,13);
	
	delete_AVL(&avl,21);
	delete_AVL(&avl,19);
	delete_AVL(&avl,22);
	
	printf("AVL tree is : \n");
	print_preorder(avl);
	
	printf("Morris traversal is : \n");
	morris_traversal(avl);
	//print_levelorder(t,h);
}	



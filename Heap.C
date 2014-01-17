/**************************************************************************************************************************************************************************************

Heap:- Heap is a ADT where root is bigger or smaller than the children and this property hold through out the tree. Left child can be bigger than right child of same parent and vice versa.
       If it is viewed as array, index (i) is bigger than 2*i and 2*i+1. Since array is zero indexing, i is bigger than 2*i+1 and 2*i+2.
	
Types of heap :- Max heap - Root is bigger than children. Min heap - Root is smaller than children.

Heap sort :- Sorting of elements over the heap data structure is heap sort. Three steps in heap sort are:
             
	     1) Heapify the entire array to hold the heap property. 
	     2) Swap last element with the first element because max heapified array has the maximum element in the first index or root. By swapping largest element would go to end.
	     3) Reduce the size by 1.
	     4) Max heapify again with the reduced size (leaving the last swapped element) which makes second largest element in the root. Repeat this step until the size is zero to
	        sort all elements. 
		
Worst case of heapify :- O(n) - for loop from backward and O(n log n) - for loop from forward because may be more than one heapify.	
		
Heap sort properties:-

                    1) In place algorithm, not using the extra space. Uses same array to swap and sort.
		    2) Not stable sort, if duplicate elements are there the position of the duplicate elements can be changed after sort.
		    
Worst case of heap sort :- O(n) (First heapify) + (n-1) log n (heapify from forward) + O(1) (for other operations)
                           http://cs.stackexchange.com/questions/4578/why-does-heapsort-run-in-thetan-log-n-instead-of-thetan2-log-n-time?rq=1

**************************************************************************************************************************************************************************************/
#include<iostream>
#include<stdio.h>
using namespace std;
int left(int i)
{
	return 2*i+1;
}
int right(int i)
{
	return 2*i+2;
}
void max_heapify(int A[],int index,int size) // By end of max heapify, maximum element of the array is in root of the tree.
{
	int l=left(index);
	int r=right(index);
	int largest=0;
	
	if (l < size && A[l] > A[index])
		largest=l; //Largest is in left side
	else
		largest=index;
	
	if (r <size && A[r] > A[largest])//If right side larger than left side which is again larget than root.
		largest=r; //Largest is in right side. So making it as root, would satisy heap property (Root is bigger than left and right).
	
	if (largest != index)
	{
		int temp=A[largest];
		A[largest]=A[index];
		A[index]=temp;
		
		max_heapify(A,largest,size);//After swapping, swapped element would have voilated the heap property from the index to below the array. So heapify again.
	}	
	
}
void heap_sort(int A[],int size) //Starts with heapified array which has biggest element of the array in root.
{
	while (size > 0)
	{
		int temp=A[0]; //Push biggest element to end of the array.
		A[0]=A[size-1];
		A[size-1]=temp;
		size=size-1; // Repeat until the size is zero.
		
		max_heapify(A,0,size); // Heapify to bring the next largest element to the root.
	}
}	
void find_K_largest(int A[],int size,int k)
{
	printf("The [%d] largest element is :",k);
	int count=1;
	while (count <= k)
	{
		printf("%d ",A[0]);
		
		int temp=A[0];
		A[0]=A[size-1];
		A[size-1]=temp;
			
		size=size-1;
		count=count+1;
		
		max_heapify(A,0,size);
	}

	cout<<endl;
}	
int main()
{
	int A[]={1,21,20,4,15,6,90,10};
	int n=sizeof(A)/sizeof(A[0]);
	int index=0;
	//max_heapify(A,index,n);
	
	for (int i=n;i>=0;i--)
	max_heapify(A,i,n);//Heapifing from the leaves or end of index will bubble up the largest element to the root and heap property in the overall tree would be maintained.
	
	/*for (int i=0;i<n;i++) // If heapified from start index to end index, then every index will have the heap property but overall tree may not have the property. Example above array.
	max_heapify(A,i,n);*/
	
		
	for (int i=0;i<n;i++)
	{
		printf("%d ",A[i]);
	}
	cout<<endl;
	
	heap_sort(A,n);
	
	cout<<"After heap sort : ";
	for (int i=0;i<n;i++)
	{
		printf("%d ",A[i]);
	}
	cout<<endl;
	
	int B[]={4,7,12,39,3,28,100};
	
	int size=sizeof(B)/sizeof(B[0]);
	
	for (int i=size;i>=0;i--)
	max_heapify(B,i,size);
	
	int k=4;
	
	find_K_largest(B,size,k);// Worst case O(nk).
	
	
}	

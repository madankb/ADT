/******************************************************************************************************************************************************************************************
Bipartite graph :- A graph which vertices can be divided into two groups, vertices in the same group is not connected to each other. The edges are only between the vertices of two sets not
                   in the same set.
		   
Example :-
        1) Many people applying for different jobs, but one job can be assigned to only one person.

        2) Family wanting the DVD of their favorite singers, but only one DVD can be assigned to a person.
	
Maximum bipartite matching :- Maximum number of people can get the jobs with constraint of only one job is assigned to one person. Maximum number of people can successfully own the DVD's.
                              In graph only there are no more than one edge goes to vertex of other set (or) Maximum number of one to one matching.
			      
Below example :- Eventhough five people applied for different jobs, only four can get the jobs.			      

Time complexity :- O(M*N).
*******************************************************************************************************************************************************************************************/
#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<string.h> //It is the header for memset, you got compilation error without it.
#define M 6
#define N 6
using namespace std;
bool assign_match(int bG[M][N],int u,bool seen[N],int mJob[N])
{
	for (int v=0;v<N;v++)
	{
		if (bG[u][v] > 0 && !seen[v])//Same job should not be assigned to that person during conflict.
		{
			seen[v]=true;//When the job is assigned to someone else try to pull the job from that person and assign different job for that person. It is acheived below.
			
			if (mJob[v] == -1 || assign_match(bG,mJob[v],seen,mJob))//If the jobs is not "-1" alreayd assigned to different person,try to assign different job for other person.
			{
				mJob[v]=u;
				return true;
			}	
		}
	}

	return false;
}	
int BPM(int bG[M][N])
{
	int result=0;
	
	int mJob[N];
	memset(mJob,-1,sizeof(mJob));
	
	for (int u=0;u<M;u++)
	{
		bool seen[N];
		memset(seen,0,sizeof(seen));
		
		if (assign_match(bG,u,seen,mJob))
			result++;
		
	}
	
	for (int i=0;i<N;i++)
	{
		if (mJob[i] != -1)
			printf("Job id %d is assigned to the person %d \n",i,mJob[i]);
	}
	
	return result;
}	
int main()
{
	int bG[M][N]={{0,1,1,0,0,0},
	              {0,0,0,0,0,0},
		            {1,0,0,1,0,0},
		            {0,0,1,0,0,0},
                {0,0,1,1,0,0},
		            {0,0,0,1,0,0}};
		
	printf("Maximum bipartite matching is : %d \n",BPM(bG));
		      
     
};


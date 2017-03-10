#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<limits.h>

long long int time = 0;
long long int counter = 0;
long long int finish[100005][2];

typedef struct node{
	long long int val;
	long long int status;
	long long int component;
	struct node * next;
}Node;

int mn=1,stack[100005];

void dfs(Node arr[], long long int i, long long int j)
{
	arr[i].status = 1;
	arr[i].component = j;
	Node * temp = arr[i].next;

		while(temp != NULL)
		{
			if(arr[temp->val].status == 0)
			{
				dfs(arr, temp->val, j);
			}
			temp=temp->next;
		}
		arr[i].status = 2;
		if(j == 0)
		{
			stack[mn]=i;
			mn++;
		}
		return;
}

void kosaraju(Node arr[], Node arr1[], long long int cost[], long long int min[100005][2], long long int n)
{
	long long int i;

	for(i = 1; i <= n; i++)
		if(arr[i].status == 0)
			dfs(arr, i, 0);

	for(i = mn-1; i > 0; i--)
	{
		if(arr1[stack[i]].component == 0)
		{
			dfs(arr1,stack[i], ++counter);
		}
	}
	
	for(i = 1; i <= n; i++)
	{
		if(cost[i] < min[arr1[i].component][0])
		{
			min[arr1[i].component][0] = cost[i];
			min[arr1[i].component][1] = 1;
		}
		else if(cost[i] == min[arr1[i].component][0])
		{
			min[arr1[i].component][1]++;
		}
	}

	return;
}

long long int temp1, temp2, count[100005], count1[100005], cost[100005];
long long int temp3, temp4, min[100005][2]={0};
int main ()

{
	int p;

	scanf("%d", &p);

	while (p--)
	{
		long long i, j, q, n, m;
		Node arr[100005], arr1[100005];
		Node * temp = NULL;
		temp1=0;
		temp2=0;
		temp3=0;
		temp4=0;


		for(i = 0; i < 100005; i++)
		{
			count[i] = 0;
			count1[i]=0;
			cost[i]=0;
			min[i][0]=INT_MAX;
			min[i][1]=1;
			arr[i].status = 0;
			arr[i].component = 0;
			arr[i].next = NULL;
			arr1[i].status = 0;
			arr1[i].component = 0;
			arr1[i].next = NULL;
		}
		time=0;
		counter = 0;
		mn=1;

		scanf("%lld %lld", &n, &m);

		for(i = 1; i <= n; i++)
			scanf("%lld", &cost[i]);

		for(i = 0; i < m; i++)
		{
			scanf("%lld %lld", &temp1, &temp2);

			if(temp1 != temp2)
			{
				count[temp1] = 1;
				count1[temp2] = 1;

				//creating adjacency lists

				Node * n = (Node *)malloc(sizeof(Node));
				n->val = temp2;
				n->next = arr[temp1].next;
				arr[temp1].next = n;

				Node * z = (Node *)malloc(sizeof(Node));
				z->val = temp1;
				z->next = arr1[temp2].next;
				arr1[temp2].next = z;
			}
		}

		kosaraju(arr, arr1, cost, min, n);

		temp4 = 0;
		temp3 = 1;

		for(i = 1; i <= counter; i++)
		{
			temp4 += min[i][0];
			temp3 = (temp3*min[i][1])%1000000007;
		}

		printf("%lld %lld\n", temp4, temp3);

		for(i = 0; i < 100005; i++)
		{
			//freeing adjacency lists

			if(count[i] == 1)
			{
				count[i] = 0;
				temp = arr[i].next;
				while(temp != NULL)
				{
					arr[i].next = temp->next;
					free(temp);
					temp = arr[i].next;
				}
			}

			if(count1[i] == 1)
			{
				count1[i] = 0;
				temp = arr1[i].next;
				while(temp != NULL)
				{
					arr1[i].next = temp->next;
					free(temp);
					temp = arr1[i].next;
				}
			}
		}
	}

	return 0;
}

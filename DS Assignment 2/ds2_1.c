#include<stdio.h>
#include<malloc.h>

typedef struct node{
	int val;
	int status;
	int indegree;
	int outdegree;
	struct node * next;
}Node;

void dfs(Node arr[], int i)
{
	arr[i].status = 1;
	Node * temp = arr[i].next;

	while(temp != NULL)
	{
		if(arr[temp->val].status == 0)
		{
			dfs(arr, temp->val);
		}
		temp=temp->next;
	}
	arr[i].status = 2;
	return;
}


int main ()
{
	int p, q, n, m, i, j, temp1, temp2, flag, count[100001], nullcount;
	Node arr[100001];
	Node * temp = NULL;

	scanf("%d", &p);

	for(q=0; q<p; q++)
	{
		nullcount++;
		flag = 0;

		for(i = 0; i < 100001; i++)
		{
			count[i] = 0;
			arr[i].status = 0;
			arr[i].indegree = 0;
			arr[i].outdegree = 0;
			arr[i].next = NULL;
		}

		flag = 0;

		scanf("%d %d", &n, &m);

		for(i = 0; i < m; i++)
		{
			scanf("%d %d", &temp1, &temp2);
			arr[temp1].outdegree++;
			arr[temp2].indegree++;

			if(temp1 != temp2)
			{
				count[temp1] = 1;
				Node * n = (Node *)malloc(sizeof(Node));
				n->val = temp2;
				n->next = arr[temp1].next;
				arr[temp1].next = n;
			}
		}

		for(i = 1; i <= n; i++)
		{
			if(arr[i].indegree != arr[i].outdegree)
			{
				printf("No\n");
				flag = 1;
				break;
			}
		}

		if((arr[n].indegree == 0)&&(n != 1)&&(flag==0))
		{
			printf("No\n");
			flag = 1;
		}

		if(flag == 0)
		{
			dfs(arr, 1);
			for(i = 1; i <= n; i++)
				if((arr[i].status != 2)&&(arr[i].indegree != 0))
				{
					printf("No\n");
					flag = 1;
					break;
				}
		}

		if(flag == 0)
			printf("Yes\n");

		for(i = 0; i < 100001; i++)
		{
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
		}
	}

	return 0;
}

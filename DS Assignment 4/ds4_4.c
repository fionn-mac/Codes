#include<stdio.h>
#include<malloc.h>

long long int n, pop[200001];

typedef struct node{
	int val;
	int index;
	int status;
	struct node * next;
}Node;

int dfs(Node arr[], int i)
{
	int count = 0, answer = 0;

	arr[i].status = 1;
	
	Node * temp = arr[i].next;

	while(temp != NULL)
	{
		if(arr[temp->val].status == 0)
		{
			answer = dfs(arr, temp->val) + 1;
			pop[temp->index] = answer;
			count += answer;
		}
		temp=temp->next;
	}
	arr[i].status = 2;
	return count;
}


int main ()

{
	int t, i, j, temp1, temp2;
	Node arr[200001];
	Node * temp = NULL;

	scanf("%d", &t);

	while(t--)
	{
		for(i = 0; i < 200001; i++)
		{
			arr[i].val = i;
			arr[i].status = 0;
			arr[i].next = NULL;
		}

		scanf("%lld", &n);

		for(i = 0; i < n-1; i++)
		{
			scanf("%d %d", &temp1, &temp2);
			
			//creating adjacency list
			Node * n = (Node *)malloc(sizeof(Node));
			n->val = temp2;
			n->index = i;
			n->next = arr[temp1].next;
			arr[temp1].next = n;

			Node * z = (Node *)malloc(sizeof(Node));
			z->val = temp1;
			z->index = i;
			z->next = arr[temp2].next;
			arr[temp2].next = z;
		}

		temp1 = dfs(arr, 1);

		for(i = 0; i < n-1; i++)
			printf("%lld ", (n - pop[i])*pop[i]);
		printf("\n");

		for(i = 0; i < 200001; i++)
		{
			//freeing adjacency list
			temp = arr[i].next;
			while(temp != NULL)
			{
				arr[i].next = temp->next;
				free(temp);
				temp = arr[i].next;
			}
		}
	}

	return 0;
}

#include<stdio.h>
#include<malloc.h>
#include<limits.h>

typedef struct node{
	int val;
	int level;
	int pleasure;
	int status;
	struct node * next;
}Node;

int max(int wow[], int j)
{
	int i, maxi = 0;

	for(i = 0; i < j; i++)
		if(wow[i] > maxi)
			maxi = wow[i];
	return maxi;
}

int min(int wow[], int j)
{
	int i, mini = INT_MAX;

	for(i = 0; i < j; i++)
		if(wow[i] < mini)
			mini = wow[i];
	return mini;
}

int dfs(Node arr[], int i, int level)
{
	int j = 0, wow[200001];

	arr[i].status = 1;
	arr[i].level = level;
	
	Node * temp = arr[i].next;
	
	while(temp != NULL)
	{
		if(arr[temp->val].status == 0)
		{
			wow[j++] = dfs(arr, temp->val, level + 1);
		}
		temp=temp->next;
	}
	arr[i].status = 2;

	if (arr[i].level % 2 == 0 && arr[i].pleasure == -1)
		arr[i].pleasure = max(wow, j);
	else if (arr[i].level % 2 == 1 && arr[i].pleasure == -1)
		arr[i].pleasure = min(wow, j);

	return arr[i].pleasure;
}

int main ()

{
	int t, i, j, n, temp1, temp2, answer;
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

		scanf("%d", &n);

		for(i = 0; i < n-1; i++)
		{
			scanf("%d %d", &temp1, &temp2);
			
			//creating adjacency list
			Node * n = (Node *)malloc(sizeof(Node));
			n->val = temp2;
			n->next = arr[temp1].next;
			arr[temp1].next = n;

			Node * z = (Node *)malloc(sizeof(Node));
			z->val = temp1;
			z->next = arr[temp2].next;
			arr[temp2].next = z;
		}

		for(i = 1; i <= n; i++)
			scanf("%d", &arr[i].pleasure);

		answer = dfs(arr, 1, 0);

		printf("%d\n", answer);

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

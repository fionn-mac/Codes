#include<stdio.h>
#include<malloc.h>

typedef struct node{
	int val;
	int status;
	int distance;
	int weight;
	struct node * next;
}Node;

void dfs(Node arr[], int i, int depth)
{
	arr[i].status = 1;
	arr[i].distance = depth;

	Node * temp = arr[i].next;

	while(temp != NULL)
	{
		if(arr[temp->val].status == 0)
		{
			dfs(arr, temp->val, depth + temp->weight);
		}
		temp=temp->next;
	}
	
	return;
}

int main()

{
	int n, i, j, x, y, w, sum = 0, max = 0, count[100001];
	Node arr[100001];
	Node * temp = NULL;


	for(i = 0; i < 100001; i++)
	{
		count[i] = 0;
		arr[i].status = 0;
		arr[i].weight = 0;
		arr[i].distance = 0;
		arr[i].next = NULL;
	}

	scanf("%d", &n);

	for(i = 1; i < n; i++)
	{
		scanf("%d %d %d", &x, &y, &w);

		count[x] = 1;
		count[y] = 1;
		sum += w;
		//creating adjacency list
		Node * n = (Node *)malloc(sizeof(Node));
		n->val = y;
		n->weight = w;
		n->next = arr[x].next;
		arr[x].next = n;

		Node * z = (Node *)malloc(sizeof(Node));
		z->val = x;
		z->weight = w;
		z->next = arr[y].next;
		arr[y].next = z;
	}

	dfs(arr, 1, 0);

	for(i = 1; i <= n; i++)
		if(arr[i].distance > max)
			max = arr[i].distance;

	printf("%d\n",2*sum - max);

	for(i = 0; i < 100001; i++)
	{
		//freeing adjacency list
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

	return 0;
}

#include<stdio.h>
#include<malloc.h>

long long int wow = 1000000007;
long long int number = 0;

int count[1000001];

typedef struct node{
	long long int val;
	int status;
	long long int level;
	struct node * next;
}Node;

Node arr[1000001];

long long int mult(Node arr1[])
{
	long long int answer = 1;
	Node * temp = arr1[0].next;
	while(temp != NULL)
	{
		answer = (answer*(temp->val))%wow;
		arr1[0].next = temp->next;
		free(temp);
		temp = arr1[0].next;
	}
	return answer;
}

int dfs(Node arr[], int i)
{
	arr[i].status = 1;
	Node * temp = arr[i].next;
	Node arr1[1];
	arr1[0].next = NULL;

	if(temp == NULL)
	{
		arr[i].level = 1;
		number++;
		if(number > wow)
			number = number%wow;
		return 1;
	}
	else
	{
		while(temp != NULL)
		{
			if(arr[temp->val].status == 0)
			{
				Node * n = (Node *)malloc(sizeof(Node));
				n->next = arr1[0].next;
				arr1[0].next = n;
				n -> val = dfs(arr, temp->val) + 1;
			}
			temp=temp->next;
		}
		arr[i].status = 2;
		arr[i].level = mult(arr1);
		number += arr[i].level;
		if(number > wow)
			number = number%wow;
		return arr[i].level;
	}
}

int main()

{
	int p, q, n, i, j, temp1, temp2;
	long long int kachra;
	Node * temp = NULL;

	scanf("%d", &p);

	for(q=0; q<p; q++)
	{
		number = 0;
		for(i = 0; i < 1000001; i++)
		{
			count[i] = 0;
			arr[i].status = 0;
			arr[i].next = NULL;
		}

		scanf("%d", &n);

		for(i = 0; i < n-1; i++)
		{
			scanf("%d %d", &temp1, &temp2);
			
			if(temp1 != temp2)
			{
				count[temp1] = 1;
				//creating adjacency list
				Node * n = (Node *)malloc(sizeof(Node));
				n->val = temp2;
				n->next = arr[temp1].next;
				arr[temp1].next = n;
			}
		}

		kachra = dfs(arr, 1);

		printf("%lld\n", number);

		for(i = 0; i < 1000001; i++)
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
	}

	return 0;
}

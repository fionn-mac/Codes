#include<stdio.h>
#include<malloc.h>

int flag = 0;

typedef struct node{
	int val;
	int statusd;
	int level;
	struct node * next;
}Node;

int count[500005], count1[500005], queue[500005], sieve[5000000], primes[5000000];
Node arr[500005], arr1[500005];

void dfs(Node arr[], int i)
{
	arr[i].statusd = 1;	
	Node * temp = arr[i].next;

	while(temp != NULL)
	{
		if(arr[temp->val].statusd == 0)
		{
			dfs(arr, temp->val);
		}

		else if(arr[temp->val].statusd == 1)
		{
			flag = 1;
			return;
		}

		temp = temp->next;
	}
	arr[i].statusd = 2;
	return;
}

int levels(Node arr1[], int i)
{
	int temp1, max = 0;
	Node * temp = arr1[i].next;

	if((temp == NULL)||(i==0))
		return 0;

	while(temp != NULL)
	{
		if (arr1[temp->val].level == -1)
		{
			temp1 = levels(arr, temp->val);
			if (max < temp1)
				max = temp1;
		}

		else if (max < arr1[temp->val].level)
			max = arr1[temp->val].level;		
		temp = temp->next;
	}
	arr1[i].level = max + 1;
	return max + 1;
}

int main ()
{
	int p, q, k, m, n, temp1, temp2;
	long long int cost, i, j;
	Node * temp = NULL;

	for (i = 0; i < 5000000; i++)
	{
		sieve[i] = 1;
		primes[i] = 0;
		if(i < 500005)
		{
			arr[i].level = -1;
			arr[i].val = i; 
			arr1[i].val = i;
		}
	}

	arr[0].level = 0;
	primes[0] = 0;
	sieve[0] = 0;
	sieve[1] = 0;
	sieve[4] = 0;
	sieve[6] = 0;

	k = 1;

	for (i = 2; i < 5000000; i++)
	{
		if (sieve[i] != 0)
		{
			primes[k++] = i;
			for(j = i; i*j < 5000000; j++)
			{
				sieve[i*j] = 0;
			}
		}
	}

	scanf("%d", &p);

	for(q = 0; q < p; q++)
	{
		cost = 0;
		flag = 0;

		for(i = 0; i < 500005; i++)
		{
			count[i] = 0;
			count1[i] = 0;
			arr[i].next = NULL; 
			arr1[i].next = NULL;
			arr[i].statusd = 0;
			arr1[i].level = -1;
		}

		scanf("%d %d", &n, &m);

		for(i = 0; i < m; i++)
		{
			scanf("%d %d", &temp1, &temp2);

			if(temp1 != temp2)
			{
				count[temp2] = 1;
				//creating adjacency list
				Node * n = (Node *)malloc(sizeof(Node));
				n->val = temp1;
				n->next = arr[temp2].next;
				arr[temp2].next = n;

				count1[temp1] = 1;
				if(temp2 == 0)
					arr[temp1].level = 1;
                                Node * z = (Node *)malloc(sizeof(Node));
				z->val = temp2;
				z->next = arr1[temp1].next;
				arr1[temp1].next = z;
			}
		}

		for(i = 0; i < n; i++)
			if(arr[i].statusd == 0)
				dfs(arr, i);

		if(flag == 1)
			printf("evil emperor loses\n");

		else
		{
			for(i = 0; i < n; i++)
				if(count1[i] == 0)
					arr1[i].level = 0;

			for(i = 0; i < n; i++)
				if(arr1[i].level == -1)
					temp1 = levels(arr1, i);

			for(i = 0; i < n; i++)
			{
				cost += primes[arr1[i].level];
			}
			printf("%lld\n", cost);
		}

		for(i = 0; i < 500005; i++)
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

#include<stdio.h>
#include<malloc.h>
#include<limits.h>

int heapsize;

typedef struct node2{
	int index;
	int vertex;
	long long int weight;
}Node2;

typedef struct node{
	int val;
	long long int weight;
	int status;
	struct node * next;
}Node;

Node2 heap[100001];
int count[100001];

void minheapify1(Node2 heap[], int i, int heapsize)
{
	int l, r, smallest = i;
	Node2 temp;

	l = 2*i + 1;
	r = 2*i + 2;

	if((l <= heapsize)&&(heap[l].weight <= heap[i].weight))
		smallest = l;

	if((r <= heapsize)&&(heap[r].weight <= heap[smallest].weight))
		smallest = r;

	if(smallest != i)
	{
		temp = heap[smallest];
		heap[smallest] = heap[i]; 
		heap[i] = temp;
		count[heap[i].vertex]=i;
		count[heap[smallest].vertex]=smallest;
		minheapify1(heap, smallest, heapsize);
	}
	return;
}

void minheapify2(Node2 heap[], int l, int heapsize)
{
	int i, r, smallest = 0;
	Node2 temp;

	if(l == 0)
		return;

	i=l;
	while(i && (heap[(i-1)/2].weight>heap[i].weight))
	{
		temp = heap[(i-1)/2]; 
		heap[(i-1)/2] = heap[i]; 
		heap[i] = temp; 
		count[heap[i].vertex] = i;
		count[heap[(i-1)/2].vertex]=(i-1)/2;
		i=(i-1)/2;
	}
	return;
}

void minheap(Node2 heap[], int l, int r)
{
	int i;
	for(i = r+1/2; i >= 0; i--)
		minheapify1(heap, i, r);
	return;
}

Node2 getmin(Node2 arr[])
{
	Node2 temp = heap[0];
	count[heap[heapsize].vertex]=count[heap[0].vertex];
	heap[0] = heap[heapsize--];
	minheapify1(heap, 0, heapsize);
	return temp;
}

long long int Prims(Node arr[])
{
	long long int wow = 0;
	Node * temp = NULL;
	Node2 queue;

	while(heapsize != 0)
	{
		queue = getmin(heap);
		arr[queue.vertex].status = 1;
		wow += queue.weight;
		temp = arr[queue.vertex].next;
		while(temp != NULL)
		{
			if(arr[temp->val].weight > temp->weight && arr[temp->val].status != 1)
			{
				arr[temp->val].weight = temp->weight;
				heap[count[temp->val]].weight = temp->weight;
				minheapify2(heap, count[temp->val], heapsize);
			}
			temp = temp->next;
		}
	}
	return wow;
}

int main ()

{
	int t, n, m, i, j, s, d, temp1, temp2;
	long long int temp3, pleasure, wow;
	Node arr[100001];
	Node * temp = NULL;

	scanf("%d", &t);

	while(t--)
	{
		pleasure = 0;
		j = 0;

		for(i = 0; i < 100001; i++)
		{
			count[i] = -1;
			arr[i].val = i;
			arr[i].status = 0;
			arr[i].weight = INT_MAX;
			arr[i].next = NULL;
			heap[i].index = i;
			heap[i].vertex = 0;
			heap[i].weight = INT_MAX;
		}

		scanf("%d %d", &n, &m);

		heapsize = n;

		for(i = 0; i < m; i++)
		{
			scanf("%d %d %lld", &temp1, &temp2, &temp3);
			
			if(i == 0)
				arr[temp1].weight = 0;

			pleasure += temp3;

			if(count[temp1] == -1)
			{
				count[temp1] = j;
				heap[j++].vertex = temp1;
			}

			if(count[temp2] == -1)
			{
				count[temp2] = j;
				heap[j++].vertex = temp2;
			}

			if (temp1 != temp2)
			{
				//creating adjacency list
				Node * n = (Node *)malloc(sizeof(Node));
				n->val = temp2;
				n->weight = temp3;
				n->next = arr[temp1].next;
				arr[temp1].next = n;

				Node * z = (Node *)malloc(sizeof(Node));
				z->val = temp1;
				z->weight = temp3;
				z->next = arr[temp2].next;
				arr[temp2].next = z;
			}
		}

		heap[0].weight = 0;
	
		minheap(heap, 0, n-1);

		wow = Prims(arr);

		printf("%lld\n", pleasure - wow);

		for(i = 0; i < 100001; i++)
		{
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

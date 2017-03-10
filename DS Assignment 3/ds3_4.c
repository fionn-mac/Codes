#include<stdio.h>
#include<malloc.h>
#include<limits.h>

int tax = 0;
int heapsize;

typedef struct node2{
	int index;
  	int vertex;
  	int weight;
}Node2;

typedef struct node{
	int val;
	int weight;
	struct node * next;
}Node;

Node2 heap[100001];
int count[100001];

void minheapify1(Node2 heap[], int i, int heapsize)
{
	int l, r, smallest = i;
	Node2 temp;
	int temp1;

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
	int temp1;

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

int max(int a, int b)
{
	if(a >= b)
		return a;
	else
		return b;
}

Node2 getmin(Node2 arr[])
{
	Node2 temp = heap[0];
	count[heap[heapsize].vertex]=count[heap[0].vertex];
  	heap[0] = heap[heapsize--];
	minheapify1(heap, 0, heapsize);
	return temp;
}

void dijkstra(Node arr[])
{
	int i;
	Node * temp = NULL;
	Node2 queue;
	
	while(heapsize != 0)
	{
  		queue = getmin(heap);
  		temp = arr[queue.vertex].next;
		while(temp != NULL)
  		{
			tax = max(arr[queue.vertex].weight, temp->weight);
  			if(arr[temp->val].weight >= tax)
			{
  				arr[temp->val].weight = tax;
				heap[count[temp->val]].weight = tax;
				minheapify2(heap,count[temp->val],heapsize);
			}
  			temp = temp->next;
  		}
	}
	return;
}

int main ()

{
	int p, q, n, m, i, j, s, d, temp1, temp2, temp3;
	Node arr[100001];
	Node * temp = NULL;

	scanf("%d", &p);

	for(q=0; q<p; q++)
	{
		tax = 0;

		for(i = 0; i < 100001; i++)
		{
			count[i] = -1;
			arr[i].val = i;
			arr[i].weight = INT_MAX;
			arr[i].next = NULL;
			heap[i].index = i;
			heap[i].vertex = 0;
			heap[i].weight = INT_MAX;
		}
		
		scanf("%d %d", &n, &m);

		j = 0;

		for(i = 0; i < m; i++)
		{
			scanf("%d %d %d", &temp1, &temp2, &temp3);
			if(count[temp2] == -1)
			{
				count[temp2] = j;
				heap[j++].vertex = temp2;
			}
			//creating adjacency list
			Node * n = (Node *)malloc(sizeof(Node));
			n->val = temp2;
			n->weight = temp3;
			n->next = arr[temp1].next;
			arr[temp1].next = n;
		}
		scanf("%d %d", &s, &d);

		int flag = 0;
		for(i = 0; i < j; i++)
			if(heap[i].vertex == s)
			{
				flag = 1;
				break;
			}
		if(flag == 0)
		{
			heapsize = j;
			heap[j].vertex = s;
			heap[j].weight = 0;
		}

		else
		{
			heapsize = --j;
			heap[i].weight = 0;
		}
		
		minheap(heap, 0, heapsize);
		
		arr[s].weight = 0;
		dijkstra(arr);
		if(arr[d].weight == INT_MAX)
			printf("NO PATH\n");
		else
			printf("%d\n", arr[d].weight);

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

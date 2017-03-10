#include<stdio.h>

typedef struct node{
	int l;
	int r;
	int v;
}Node;

int arr[1000001][2];
Node stack[100001];

void merge(Node arr[], int l, int m, int r)
{
	Node arr1[m-l+1], arr2[r-m];
	int i, j, k;

	for(i = 0; i < m-l+1; i++)
	{
		arr1[i].l = arr[l+i].l;
		arr1[i].r = arr[l+i].r;
		arr1[i].v = arr[l+i].v;
	}

	for(j = 0; j < r-m; j++)
	{
		arr2[j].l = arr[j+m+1].l;
		arr2[j].r = arr[j+m+1].r;
		arr2[j].v = arr[j+m+1].v;
	}

	i = 0;
	j = 0;
	k = l;

	while((i< m-l+1) && (j < r-m))
	{
		if((arr1[i].v < arr2[j].v)||(arr1[i].v == arr2[j].v && (arr1[i].r - arr1[i].l < arr2[j].r - arr2[j].l)))
		{
			arr[k].l = arr1[i].l;
			arr[k].r = arr1[i].r;
			arr[k++].v = arr1[i++].v;
		}
		else
		{
			arr[k].l = arr2[j].l;
			arr[k].r = arr2[j].r;
			arr[k++].v = arr2[j++].v;
		}
	}

	while(i < m-l+1)
	{
		arr[k].l = arr1[i].l;
		arr[k].r = arr1[i].r;
		arr[k++].v = arr1[i++].v;
	}
	while(j < r - m) 
	{
		arr[k].l = arr2[j].l;
		arr[k].r = arr2[j].r;
		arr[k++].v = arr2[j++].v;
	}
}

void mergesort(Node arr[], int l, int r)
{
	if(l < r){
		int m = l + (r - l)/2;
		mergesort(arr, l , m);
		mergesort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

int main ()
{
	int p, q, n, i, j, li, ri, vi, max = 0;

	scanf("%d", &p);

	for(q = 0; q < p; q++)
	{
		for(i = 0; i < 1000001; i++)
			arr[i][0] = 0;

		scanf("%d", &n);

		for(i = 0; i < n; i++)
		{
			scanf("%d %d %d", &stack[i].l, &stack[i].r, &stack[i].v);
			if(max < stack[i].r)
				max = stack[i].r;
		}

		mergesort(stack, 0, n-1);

		for(i = n - 1; i >= 0; i--)
		{
			j = stack[i].l;
			while(j < stack[i].r)
			{
				if(arr[j][0] < stack[i].v)
				{
					arr[j][0] = stack[i].v;
					arr[j++][1] = stack[i].r;
				}
				else if(arr[j][0] >= stack[i].v)
				{
					j = arr[j][1];
				}
			}
		}

		for(i = 0; i < max; i++)
			if(arr[i][0] != 0)
				break;
		while(i <= max)
		{
			if(arr[i][0] != arr[i-1][0])
				printf("%d %d\n", i, arr[i][0]);
			i++;
		}
	}

	return 0;
}

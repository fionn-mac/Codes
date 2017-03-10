#include<stdio.h>

int arr[200005], stree[800004], sort[200005], indices[200005];

typedef struct node{
	char command;
	int val;
}Node;

Node input[200005];

void merge(int arr[], int l, int m, int r)
{
	int arr1[m-l+1], arr2[r-m], i, j, k;

	for(i = 0; i < m-l+1; i++)
		arr1[i] = arr[l+i];

	for(j = 0; j < r-m; j++)
		arr2[j] = arr[j+m+1];

	i = 0;
	j = 0;
	k = l;

	while((i< m-l+1) && (j < r-m))
	{
		if(arr1[i] <= arr2[j])
			arr[k++] = arr1[i++];
		else
			arr[k++] = arr2[j++];
	}

	while(i < m-l+1)
		arr[k++] = arr1[i++];
	while(j < r - m)
		arr[k++] = arr2[j++];

}

void mergesort(int arr[], int l, int r)
{
	if(l < r){
		int m = l + (r - l)/2;
		mergesort(arr, l , m);
		mergesort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

int midterm(int a, int b)
{
	return a + (b - a)/2;
}

int rangesumutil(int tree[], int tstart, int tend, int qstart, int qend, int index)
{
	if(qstart <= tstart && qend >= tend)
		return tree[index];

	if(tend < qstart || tstart > qend)
		return 0;

	int mid = midterm(tstart, tend);
	return rangesumutil(tree, tstart, mid, qstart, qend, 2*index+1) + rangesumutil(tree, mid+1, tend, qstart, qend, 2*index+2);
}

int rangesumquery(int tree[], int n, int qstart, int qend)
{
	return rangesumutil(tree, 0, n-1, qstart, qend, 0);
}

int rangeupdateutil(int tree[], int tstart, int tend, int qstart, int qend, int index, int new)
{
	if(qstart <= tstart && qend >= tend)
	{
		tree[index] = new;
		return tree[index];
	}

	if(tend < qstart || tstart > qend)
		return tree[index];

	int mid = midterm(tstart, tend);
	tree[index] = rangeupdateutil(tree, tstart, mid, qstart, qend, 2*index+1, new) + rangeupdateutil(tree, mid+1, tend, qstart, qend, 2*index+2, new);
	return tree[index];
}

int rangeupdate(int tree[], int n, int qstart, int qend, int new)
{
	return rangeupdateutil(tree, 0, n-1, qstart, qend, 0, new);
}

int construct(int arr[], int tstart, int tend, int tree[], int nodei)
{
	if(tstart == tend)
	{
		tree[nodei] = arr[tstart];
		return arr[tstart];
	}

	int mid = midterm(tstart, tend);
	tree[nodei] = construct(arr, tstart, mid, tree, nodei*2 + 1) + construct(arr, mid+1, tend, tree, nodei*2 + 2);

	return tree[nodei];
}

int binarysearch(int key, int l, int r)
{
	int m;

	while(l <= r)
	{
		m = midterm(l, r);

		if(indices[m] == key)
			return m;

		else if (indices[m] < key)
			l = m+1;
		else
			r = m-1;
	}
	return m;
}

int main ()
{
	int i, q, j, k, l, m, r;

	for(i = 0; i < 200005; i++)
		arr[i] = 0;

	scanf("%d", &q);

	i = 0;

	while(q--)
	{
		scanf(" %c %d", &input[i].command, &input[i].val);
		sort[i] = input[i].val;
		i++;
	}

	mergesort(sort, 0, i-1);

	indices[0] = sort[0];
	
	k = 1;

	for(j = 1; j < i; j++)
	{
		if(sort[j] != sort[j-1]);
			indices[k++] = sort[j];
	}

	k--;

	q = i;

	for(i = 0; i < q; i++)
	{
		if(input[i].command == 'I')
		{
			m = binarysearch(input[i].val, 0, k);
			if(arr[m] == 0)
			{
				arr[m] = 1;
				rangeupdate(stree, 200001, m, m, 1);
			}
		}

		else if(input[i].command == 'D')
		{
			m = binarysearch(input[i].val, 0, k);
			if(arr[m] == 1)
			{
				arr[m] = 0;
				rangeupdate(stree, 200001, m, m, 0);
			}
		}

		else if(input[i].command == 'C')
		{
			m = binarysearch(input[i].val, 0, k);
			printf("%d\n", rangesumquery(stree, 200001, 0, m-1));
		}

		else if(input[i].command == 'K')
		{
			if(input[i].val > stree[0])
				printf("invalid\n");
			else
			{
				l = 0;
				r = k;

				while(l <= r)
				{
					m = midterm(l, r);
					if(rangesumquery(stree, 200001, 0, m) == input[i].val)
					{
						if(rangesumquery(stree, 200001, 0, m-1) < input[i].val)
						{
							printf("%d\n", indices[m]);
							break;
						}
						else
							r = m-1;
					}
					else if(rangesumquery(stree, 200001, 0, m) < input[i].val)
						l = m+1;
					else
						r = m-1;
				}
			}
		}
	}
	return 0;
}

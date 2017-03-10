#include<stdio.h>

int arr2[400004];

int max(int a, int b)
{
	if(a<=b)
		return b;
	else
		return a;
}

int midterm(int a, int b)
{
	return a + (b - a)/2;
}

int rangemaxutil(int tree[], int tstart, int tend, int qstart, int qend, int index)
{
	if(qstart <= tstart && qend >= tend)
		return tree[index];

	if(tend < qstart || tstart > qend)
		return 0;

	int mid = midterm(tstart, tend);
	return max(rangemaxutil(tree, tstart, mid, qstart, qend, 2*index+1), rangemaxutil(tree, mid+1, tend, qstart, qend, 2*index+2));
}

int rangemaxquery(int tree[], int n, int qstart, int qend)
{
	return rangemaxutil(tree, 0, n-1, qstart, qend, 0);
}

int construct(int arr[], int tstart, int tend, int tree[], int nodei)
{
	if(tstart == tend)
	{
		tree[nodei] = arr[tstart];
		return arr[tstart];
	}

	int mid = midterm(tstart, tend);
	tree[nodei] = max(construct(arr, tstart, mid, tree, nodei*2 + 1),construct(arr, mid+1, tend, tree, nodei*2 + 2));

	return tree[nodei];
}

int main ()
{
	int n, w, i, p, q, arr[100001];

	scanf("%d", &p);

	for(q = 0; q < p; q++)
	{
		scanf("%d %d", &n, &w);

		for(i = 0; i < n; i++)
			scanf("%d", &arr[i]);

		construct(arr, 0, n-1, arr2, 0);

		for(i = 0; i + w <= n; i++)
		{
			int qstart = i;
			int qend = i + w - 1;

			printf("%d ", rangemaxquery(arr2, n, qstart, qend));
		}
		printf("\n");
	}

	return 0;
}

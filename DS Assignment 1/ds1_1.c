#include<stdio.h>

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

int main ()
{

	int arr[200000], i, n, p, q;

	scanf("%d", &p);

	for(q = 0; q < p; q++)
	{
		scanf("%d", &n);

		for(i = 0; i < n; i++)
			scanf("%d", &arr[i]);

		mergesort(arr, 0, n-1);

		printf("%d\n", arr[n/2]);
	}

	return 0;
}

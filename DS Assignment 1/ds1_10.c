#include<stdio.h>

void merge(int arr[100001][2], int l, int m, int r)
{
	int arr1[m-l+1][2], arr2[r-m][2], i, j, k;

	for(i = 0; i < m-l+1; i++)
	{
		arr1[i][0] = arr[l+i][0];
		arr1[i][1] = arr[l+i][1];
	}

	for(j = 0; j < r-m; j++)
	{
		arr2[j][0] = arr[j+m+1][0];
		arr2[j][1] = arr[j+m+1][1];
	}

	i = 0;
	j = 0;
	k = l;

	while((i< m-l+1) && (j < r-m))
	{
		if(arr1[i][0] <= arr2[j][0])
		{
			arr[k][0] = arr1[i][0];
			arr[k][1] = arr1[i][1];
			k++;
			i++;
		}
		else
		{
			arr[k][0] = arr2[j][0];
			arr[k][1] = arr2[j][1];
			k++;
			j++;
		}
	}

	while(i < m-l+1)
	{
		arr[k][0] = arr1[i][0];
		arr[k][1] = arr1[i][1];
		k++;
		i++;
	}
	while(j < r - m)
	{
		arr[k][0] = arr2[j][0];
		arr[k][1] = arr2[j][1];
		k++;
		j++;
	}

}

void mergesort(int arr[100001][2], int l, int r)
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
	int arr[100000], arr1[100000][2], stack[100001], left[100001], right[100001], temp[100001][2], p, q, i, j, k, n;

	scanf("%d", &p);

	for(q = 0; q < p; q++)
	{

		scanf("%d", &n);

		for(i = 0; i < n; i++)
		{
			scanf("%d", &arr[i]);
			arr1[i][0] = arr[i];
			arr1[i][1] = i;
			left[i] = -1;
			right[i] = n;
		}

		mergesort(arr1, 0, n-1);

		j = -1;

		for(i = 0; i < n; i++)
		{
			while(j > -1)
			{
				if(arr[stack[j]] > arr[i])
				{
					right[stack[j]] = i;
					j--;
				}
				else
					break;
			}

			j++;
			stack[j] = i;
		}

		j = -1;

		for(i = n-1; i >= 0; i--)
		{
			while(j > -1)
			{
				if(arr[stack[j]] > arr[i])
				{
					left[stack[j]] = i;
					j--;
				}
				else
					break;
			}

			j++;
			stack[j] = i;
		}

		mergesort(arr1, 0, n-1);

		j = n-1;
		i = 0;
		k = 0;

		while(i < n)
		{
			while(k < (right[arr1[j][1]] - left[arr1[j][1]] - 1))
			{
				if(i < n-1)
					printf("%d ", arr1[j][0]);
				else if(i == n-1)
					printf("%d", arr1[j][0]); 
				k++;
				i++;
				if(i == n)
					break;
			}
			j--;
		}
		printf("\n");

	}

	return 0;
}

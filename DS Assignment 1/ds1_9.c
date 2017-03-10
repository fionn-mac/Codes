#include<stdio.h>

int main ()
{
	long long int arr[100001], sum[100001], p, q, i, j, m, l, n, k, mini, min = 10000000000;
	
	scanf("%lld", &p);

	for(q = 0; q < p ; q++)
	{
		min = 10000000000;

		for(i = 0; i < 100001; i++)
		{
			arr[i] = 0;
			sum[i] = 0;
		}

		scanf("%lld %lld", &n, &k);

		for(i = 0; i < n; i++)
		{
			scanf("%lld", &arr[i]);
			if((i > 0) && (i <= k))
			{
				sum[i] = arr[i] + arr[0];
				if(sum[i] <= min)
				{
					min = sum[i];
					mini = i;
				}
			}
		}

		l = k;

		for(i = k+1; i < n; i++)
		{
			if(i <= mini + k)
			{
				if((i < l) && (sum[i] > arr[i] + sum[mini]))
					sum[i] = arr[i]+sum[mini];
				else if(i >= l)
					sum[i] = arr[i] + sum[mini];
			}

			else
			{
				l = i;
				min = 10000000000;
				j = mini;
				for(m = j+1; m <= j+k; m++)
				{
					if(sum[m] <= min)
					{
						min = sum[m];
						mini = m;
					}
				}
				i = mini;
			}
		}

		printf("%lld\n", sum[n-1]);
	}

	return 0;
}

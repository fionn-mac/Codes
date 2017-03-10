#include<stdio.h>

long long int binarysearch(long long int arr[100001][2], long long int q, long long int l, long long int r, long long int n,  long long int weight)
{
	if(arr[r][1]*q<weight)
		return -1;
	if(arr[r][1]*q>=weight && (arr[r][1]-arr[0][1])*q<weight)
		return 0;
	while (l <= r)
	{
		long long int m = (l + r)/2;
		
		if (((arr[n][1] - arr[m-1][1])*q >= weight)&&((arr[n][1] - arr[m][1])*q < weight))
		{
			return m;
		}

		else if ((arr[n][1] - arr[m-1][1])*q < weight)
		{
			r = m - 1;
		}
		else
			l = m + 1;
	}

	return -1;
}

int main ()
{

	long long int t,p, q, n, k, i, j, l, weight[100001][2], cost[100001][2], m, max;

	scanf("%lld", &p);

	for(t = 0; t < p; t++)
	{

		scanf("%lld %lld %lld", &n, &k, &q);

		for(i = 0; i < n; i++)
		{
			scanf("%lld", &weight[i][0]);

			if(i > 0)
				weight[i][1] = weight[i][0] + weight[i-1][1];
			else
				weight[i][1] = weight[i][0];
		}

		for(i = 0; i < n; i++)
		{
			scanf("%lld", &cost[i][0]);

			if(i > 0)
				cost[i][1] = cost[i][0] + cost[i-1][1];
			else
				cost[i][1] = cost[i][0];
		}

		i = n-1;
		j = n - k;
		max = 0;

		while(j > 0)
		{
			m = binarysearch(weight, q, 0, j-1, j-1, weight[i][1] - weight[j-1][1]);

			if(m==0 && cost[n-1][1] - cost[i][1]>=max)
				max= cost[n-1][1] - cost[i][1];
			else if((m > 0)&&((cost[m-1][1] + cost[n-1][1] - cost[i][1]) >= max))
			{
				max = cost[m-1][1] + cost[n-1][1] - cost[i][1];
			}
			i--;
			j--;
		}

		printf("%lld\n", max);

	}

	return 0;
}

#include<stdio.h>

int main ()
{
	long long int answer, arr[100000], frequency[100001], p, q, n, i, k;

	scanf("%lld", &p);

	for(q = 0; q<p; q++)
	{
		answer = 0;

		for(i = 0; i < 100001; i++)
			frequency[i] = 0;
		
		scanf("%lld %lld", &n, &k);

		for(i = 0; i < n; i++)
		{
			scanf("%lld", &arr[i]);
			if(i > 0)
				arr[i] += arr[i-1];
		}

		for(i = 0; i < n; i++)
		{
			arr[i] = arr[i]%k;
			frequency[arr[i]]++;
		}

		for(i = 0; i < k; i++)
		{
			if(frequency[i] != 0)
				answer = answer + (frequency[i]*(frequency[i]-1))/2;
		}

		printf("%lld\n", (answer + frequency[0])%1000000007);
	}

	return 0;
}

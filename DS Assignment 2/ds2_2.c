#include<stdio.h>

int main ()
{

	int p, q, i, n, temp, arr[100001];

	scanf("%d", &p);

	for(q = 0; q < p; q++)
	{
		for(i = 0; i < 100001; i++)
			arr[i] = 0;

		scanf("%d", &n);

		for(i = 0; i < n; i++)
		{
			scanf("%d", &temp);
			if(temp > 100000)
				arr[100000]++;
			else
				arr[temp]++;
		}

		for(i = 99999; i >= 0; i--)
		{
			arr[i] += arr[i+1];
			if(arr[i] >= i)
			{
				printf("%d\n", i);
				break;
			}
		}
	}

	return 0;
}	

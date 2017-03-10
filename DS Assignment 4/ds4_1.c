#include<stdio.h>

int main ()
{
	int t, i, j, n, temp, max, count[100001], answer;

	scanf("%d", &t);

	while(t--)
	{
		answer = 0;
		max = 0;

		for(i = 0; i < 100001; i++)
			count[i] = 0;

		scanf("%d", &n);

		for(i = 0; i < n; i++)
		{
			scanf("%d", &temp);
			count[temp]++;
			if(count[temp] > max)
				max = count[temp];
		}

		if (max > n/2)
			printf("%d\n", max);

		else
			printf("%d\n", n/2 + n%2);
	}

	return 0;
}

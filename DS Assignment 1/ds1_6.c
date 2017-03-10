#include<stdio.h>

int main ()

{
	int p, q, i, j, k, arr1[100000], arr2[100000], arr3[100000], n1, n2, n3, count;

	scanf("%d", &p);

	for(q = 0; q < p; q++)
	{
		count = 0;

		scanf("%d", &n1);

		for(i = 0; i < n1; i++)
			scanf("%d", &arr1[i]);

		scanf("%d", &n2);

		for(i = 0; i < n2; i++)
			scanf("%d", &arr2[i]);

		scanf("%d", &n3);

		for(i = 0; i < n3; i++)
			scanf("%d", &arr3[i]);
		i = 0;
		j = 0;
		k = 0;

		while((i < n1) && (j < n2) && (k < n3))
		{
			if((arr1[i] < arr2[j]) || (arr1[i] < arr3[k]))
				i++;
			if((arr2[j] < arr1[i]) || (arr2[j] < arr3[k]))
				j++;
			if((arr3[k] < arr2[j]) || (arr3[k] < arr1[i]))
				k++;

			if((arr1[i] == arr2[j]) && (arr1[i] == arr3[k])){
				count++;
				i++;
				j++;
				k++;
			}
		}

		printf("%d\n", count);
	}

	return 0;
}

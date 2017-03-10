#include<stdio.h>
#include<string.h>

int main ()

{
	int  i, j, p, q, n;
	char arr[200001], arr2[200001]; 

	scanf("%d", &p);

	for(q = 0; q < p; q++){

		scanf("%s", arr2);

		n = strlen(arr2);

		arr[0] = arr2[0];

		j = 0;

		for(i = 1; i < n; i++)
		{
			if(((arr2[i] == ')') && (arr[j] == '(')) || ((arr2[i] == '}') && (arr[j] == '{')) || ((arr2[i] == ']') && (arr[j] == '[')))
			{
				j--;
			}
			else{
				j++;
				arr[j] = arr2[i];
			}

		}

		if(j == -1)
			printf("Yes\n");
		else
			printf("No\n");
	}

	return 0;
}

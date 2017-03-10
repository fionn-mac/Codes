#include<stdio.h>
#include<string.h>
#include<math.h>

long long int power(long long int a)
{
	long long int temp = 1000000004;
	long long int temp2 = a;
	int arr[32] = {0}; 
	long long int i, j, answer = 1;

	for(i = 0; i < 32; i++)
	{
		arr[i] = temp&1;
		temp = temp >> 1;
	}

	j = 1;

	for(i = 1; i < 32; i++)
	{
		if(arr[i] == 1)
		{
			while(j < pow(2,i)){
				a = ((a%1000000007)*(a%1000000007))%1000000007;
				j = j*2;
			}

			answer = ((answer%1000000007)*(a))%1000000007;
		}
	}
	answer = ((answer%1000000007)*(temp2))%1000000007;

	return answer;
}


long long int postfix(char arr2[200001], int l, int u)
{
	long long int arr[200001], j, i, k, temp;
	j = l-1;

	if(u < l)
		return 0;
	
	else if(u == l)
		return arr2[u] - '0';

	else{

		for(i = 0; i <= u; i++)
		{
			if((arr2[i] == '0') || (arr2[i] == '1') || (arr2[i] == '2') || (arr2[i] == '3') || (arr2[i] == '4') || (arr2[i] == '5') || (arr2[i] == '6') || (arr2[i] == '7') || (arr2[i] == '8') || (arr2[i] == '9'))  
			{
				j++;
				arr[j] = arr2[i] - '0';
			}
			else if ((arr2[i] == '+') || (arr2[i] == '-') || (arr2[i] == '/') || (arr2[i] == '*'))
			{
				j--;
				if(arr2[i] == '+')
					arr[j] = ((arr[j]) + arr[j+1])%1000000007;
				else if(arr2[i] == '*')
					arr[j] = (((arr[j])%1000000007)*(arr[j+1]))%1000000007;
				else if(arr2[i] == '/'){
					temp = power(arr[j+1]);
					arr[j] = ((arr[j]%1000000007)*temp)%1000000007;
				}
				else if(arr2[i] == '-')
					arr[j] =  ((arr[j]) - arr[j+1])%1000000007;
			}
		}

		return arr[0];
	}
}

int main ()

{
	long long int  i, p, q, n, answer;
	char arr2[200001], temp;

	scanf("%lld", &p);

	for(q = 0; q < p; q++){

		scanf("%s", arr2);

		n = strlen(arr2);

		answer = postfix(arr2, 0, n-1);

		printf("%lld\n", answer);
	}

	return 0;
}

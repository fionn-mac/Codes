#include<stdio.h>
#include<string.h>
#include<math.h>

long long int powo[1000001][2], inverse[1000001][2], yolo[300005], yolo2[300005], m1 = 1000000007, n1 = 1000000009;
char temp[300005];
int arr[32][2];

void power(long long int arr[1000001][2], int i)
{
	if(i == 0)
	{
		powo[0][0] = 1;
		powo[0][1] = 1;

		for(i = 1; i < 300005; i++)
		{
			powo[i][0] = (26*powo[i-1][0])%m1;
			powo[i][1] = (26*powo[i-1][1])%n1;
		}
	}
	return;
}

long long int hash(char str[], long long int hash1[], long long int hash2[])
{
	int i = 0;

	while(str[i] != '\0')
	{
		hash1[i] = powo[i][0]*(str[i] - 'a');
		hash2[i] = powo[i][1]*(str[i] - 'a');
		if(i > 0)
		{
			hash1[i] = (hash1[i] + hash1[i-1])%m1;
			hash2[i] = (hash2[i] + hash2[i-1])%n1;
		}
		i++;
	}

	return i;
}


long long power2(long long int a, long long int b, long long int wow)
{
	long long x=1,y=a;
	while(b > 0)
	{
		if(b%2 == 1)
		{
			x = (x*y);
			if(x > wow) 
				x = x%wow;
		}

		y = (y*y);

		if(y>wow) 
			y = y%wow;
		b = b/2;
	}
	return x;
}


long long inversemod(long long int n, long long int wow)
{
	return power2(n, wow-2, wow);
}

long long int compare(long long int hash1[], long long int hash2[], long long int hash3[], long long int hash4[], long long int hash5[], long long int hash6[], char str1[], char str2[], char str3[], long long int l1, long long int l2, long long int l3)
{
	long long int i, len = l2;
	int flag1 = 0;
	int flag2 = 0;

	if(l1 <= l2) 
	{   
		if(hash2[l1-1] == hash1[l1-1])
		{
			if(hash5[l1-1] == hash4[l1-1])
				flag1 = 1;
		}   
		else
		{   
			for(i = l1; i < l2; i++)
			{   
				if(((hash2[i] - hash2[i-l1] + m1)*inversemod(power2(26, i-l1+1, m1), m1)%m1) == hash1[l1-1])
				{
					if(((hash5[i] - hash5[i-l1] + n1)*inversemod(power2(26, i-l1+1, n1), n1)%n1) == hash4[l1-1])
					{
						flag1 = 1;
						len = l2;
						break;
					}
				}   
			}   
		}   
	}  

	else if(l2 < l1) 
	{   
		if(hash1[l2-1] == hash2[l2-1])
		{
			if(hash4[l2-1] == hash5[l2-1])
			{
				flag1 = 1;
				len = l1;
			}
		}   
		else
		{   
			for(i = l2; i < l1; i++)
			{   
				if(hash2[l2-1]  == ((hash1[i] - hash1[i-l2] + m1)*inversemod(power2(26, i-l2+1, m1), m1)%m1))
				{
					if(hash5[l2-1]  == ((hash4[i] - hash4[i-l2] + n1)*inversemod(power2(26, i-l2+1, n1), n1)%n1))
					{
						flag1 = 1;
						len = l1;
						break;
					}
				}   
			}   
		}   
	}

	if(flag1 != 1)
	{

		if(l2 > l1)
		{
			for(i = 0; i < l1-1; i++)
			{
				if(((hash1[l1-1] - hash1[i] + m1)*inversemod(power2(26, i+1, m1), m1)%m1 == hash2[l1-i-2]))
				{
					if(((hash4[l1-1] - hash4[i] + n1)*inversemod(power2(26, i+1, n1), n1)%n1 == hash5[l1-i-2]))
					{

						len = len + i + 1;
						flag1 = 1;
						break;
					}
				}
			}
		}
		else
		{
			for(i = l2-1; i >= 0; i--)
			{
				if(hash2[i] == ((hash1[l1-1] - hash1[l1-i-2] + m1)*inversemod(power2(26,l1-i-1, m1), m1)%m1))
				{
					if(hash5[i] == ((hash4[l1-1] - hash4[l1-i-2] + n1)*inversemod(power2(26,l1-i-1, n1), n1)%n1))
					{
						len = len + l1-i-1;
						flag1 = 1;
						break;
					}
				}
			}
		}
	}

	if(flag1 != 1)
	{
		len = len + l1;
	}


	if(len != l2)
	{

		long long int t = l1 + l2 - len;

		for(i = 0; i < len; i++)
		{
			if(i < l1)
				temp[i] = str1[i];
			else
				temp[i] = str2[t++];
		}
		temp[len] = '\0';
	}

	else {
		strcpy(temp, str2);
	}

	i = hash(temp, yolo, yolo2);

	if(len <= l3) 
	{   
		if(hash3[len-1] == yolo[len-1])
		{
			if(hash6[len-1] == yolo2[len-1])
			{
				len = l3;
				flag2 = 1;
			}
		}   
		else
		{   
			for(i = len; i < l3; i++)
			{   
				if(((hash3[i] - hash3[i-len] + m1)*inversemod(power2(26, i-len+1, m1), m1)%m1) == yolo[len-1])
				{ 
					if(((hash6[i] - hash6[i-len] + n1)*inversemod(power2(26, i-len+1, n1), n1)%n1) == yolo2[len-1])
					{  
						flag2 = 1;
						len = l3;
						break;
					}
				}
			}   
		}   
	}

	if(l3 < len) 
	{   
		if(yolo[l3-1] == hash3[l3-1])
		{
			if(yolo2[l3-1] == hash6[l3-1])
			{
				flag2 = 1;
			}
		}   
		else
		{
			for(i = l3; i < len; i++)
			{   
				if (hash3[l3-1] == ((yolo[i] - yolo[i-l3] + m1)*inversemod(power2(26, i-l3+1, m1), m1)%m1))
				{
					if (hash6[l3-1] == ((yolo2[i] - yolo2[i-l3] + n1)*inversemod(power2(26, i-l3+1, n1), n1)%n1))
					{

						flag2 = 1;
						break;
					}
				}
			}   
		}   
	}

	if(flag2 != 1)
	{

		if(l3 > len)
		{
			for(i = 0; i < len-1; i++)
			{
				if(((yolo[len-1] - yolo[i] + m1)*inversemod(power2(26, i+1, m1), m1)%m1 == hash3[len-i-2]))
				{
					if(((yolo2[len-1] - yolo2[i] + n1)*inversemod(power2(26, i+1, n1), n1)%n1 == hash6[len-i-2]))
					{

						len = l3 + i + 1;
						flag2 = 1;
						break;
					}
				}
			}
		}
		else
		{
			for(i = l3-1; i >= 0; i--)
			{
				if(hash3[i] == ((yolo[len-1] - yolo[len-i-2] + m1)*inversemod(power2(26,len-i-1, m1), m1)%m1))
				{
					if(hash6[i] == ((yolo2[len-1] - yolo2[len-i-2] + n1)*inversemod(power2(26,len-i-1, n1), n1)%n1))
					{

						len = len + l3 - i - 1;
						flag2 = 1;
						break;
					}
				}
			}
		}
	}


	if(flag2 != 1)
		len = len + l3;

	return len;
}

int main ()
{
	long long int i, hash1[100001], hash2[100001], hash3[100001], hash4[100001], hash5[100001], hash6[100001], l1, l2, l3, temp1[6], min=10000000;
	char str1[100001], str2[100001], str3[100001];

	scanf("%s %s %s", str1, str2, str3);

	power(powo, 0);
	power(inverse, 1);

	l1 = hash(str1, hash1, hash4);
	l2 = hash(str2, hash2, hash5);
	l3 = hash(str3, hash3, hash6);


	temp1[0] = compare(hash1, hash2, hash3, hash4, hash5, hash6, str1, str2, str3, l1, l2, l3);
	temp1[1] = compare(hash1, hash3, hash2, hash4, hash6, hash5, str1, str3, str2, l1, l3, l2);
	temp1[2] = compare(hash2, hash1, hash3, hash5, hash4, hash6, str2, str1, str3, l2, l1, l3);
	temp1[3] = compare(hash2, hash3, hash1, hash5, hash6, hash4, str2, str3, str1, l2, l3, l1);
	temp1[4] = compare(hash3, hash1, hash2, hash6, hash4, hash5, str3, str1, str2, l3, l1, l2);
	temp1[5] = compare(hash3, hash2, hash1, hash6, hash5, hash4, str3, str2, str1, l3, l2, l1);

	for(i = 0; i < 6; i++)
	{
		if(temp1[i] <= min)
		{
			min = temp1[i];
		}
	}

	printf("%lld\n", min);

	return 0;
}

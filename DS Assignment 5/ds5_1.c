#include<stdio.h>
#include<string.h>

int n, len, x, temp[100002]={0}, z[100002]={0}, freq[5005]={0};
long long int fact[5005]={0}, ifact[5005]={0}, count[5005]={0}, answer[5005]={0}, wow = 1000000007, shaata;
char string[5005]={}, suffixes[5001][5001]={}, join[100000]={};

long long int power2(long long int a, long long int b)
{
	long long x1=1,y=a;
	while(b > 0)
	{
		if(b%2 == 1)
		{
			x1 = (x1*y);
			if(x1 > wow) 
				x1 = x1%wow;
		}

		y = (y*y);

		if(y>wow) 
			y = y%wow;
		b = b/2;
	}
	return x1;
}

long long int inversemod(long long int n1)
{
	return power2(n1, wow-2);
}

void gensuffix()
{
	int i, j, k;
	for(i = 0; i <= len; i++)
	{	
		k = 0;
		for(j = i; j <= len; j++)
			suffixes[i][k++] = string[j];
	}
	return;
}

void genfact()
{
	int i;
	fact[0] = 1;
	fact[1] = 1;

	for(i = 2; i < 5001; i++)
		fact[i] = (i*fact[i-1])%wow;

	return;
}

void genifact()
{
	int i;
	ifact[0] = 1;
	ifact[1] = 1;

	for(i = 2; i < 5001; i++)
	{
		ifact[i] = (inversemod(fact[i]))%wow;
	}
	return;
}

void buildz()
{
	int i, l, r, k;
	int len2 = 0;

	while(join[len2] != '\0')
		len2++;

	l = r = 0;
	for(i = 1; i < len2; ++i)
	{
		if(i > r)
		{
			l = r = i;
			while(r < len2 && join[r-l] == join[r])
				r++;

			z[i] = r-l;
			r--;
		}
		else
		{
			k = i-l;
			if(z[k] < r-i+1)
				z[i] = z[k];
			else
			{
				l = i;
				while(r < len2 && join[r-l] == join[r])
					r++;
				z[i] = r-l;
				r--;
			}
		}
	}
	return;
}

void match()
{
	int i, j, k, l, m, n1, voila;

	for(i = 0; i <= len; i++)
	{
		j = 0;

		while(suffixes[i][j] != '\0')
		{
			join[j] = suffixes[i][j];
			j++;
		}

		l = j;

		join[j++] = '$';

		k = 0;

		while(string[k] != '\0')
			join[j++] = string[k++];

		join[j] = string[k];

		buildz();

		k = 0;

		for(n1 = l; n1 < j; n1++)
		{
			if(z[n1] > temp[k])
			{
				for(m = z[n1]; temp[k] < m ; m--)
				{
					freq[m]++;
				}
				temp[k] = z[n1];
			}
			k++;
		}

		for(n1 = 1; n1 < 5001; n1++)
		{
			count[freq[n1]]++;
			freq[n1] = 0;
		}
	}
	return;
}

int main ()

{
	int i, j;

	for(i = 0; i < 5005; i++)
	{
		freq[i] = 0;
		count[i] = 0;
		answer[i] = 0;
	}

	for(i = 0; i < 100002; i++)
		temp[i] = 0;

	genfact();
	genifact();

	scanf("%d %d", &len, &n);
	scanf("%s", string);

	gensuffix();	
	match();

	for(i = 5000; i >=1 ; i--)
	{
		for(j = i; j < 5001; j++)
		{
			shaata = (count[j]*fact[j])%wow;
			shaata = (shaata*ifact[j-i])%wow;
			shaata = (shaata*ifact[i])%wow;
			answer[i] = (answer[i] + shaata)%wow;
		}
	}

	answer[1] = ((len*(len+1))%wow)/2;
	
	for(j = 0; j < n; j++)
	{	
		scanf("%d", &x);
		
		if(x > len)
			printf("0\n");
		else
			printf("%lld\n", answer[x]);
	}
	return 0;
}

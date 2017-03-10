#include<stdio.h>
#include <math.h>

long long int inversions = 0;

long long int mergei(double arr[100001][2], int l, int m, int r)
{
	int i, j, k; 
	double arr1[m-l+1][2], arr2[r-m][2];

	for(i = 0; i < (m - l + 1); i++)
	{
		arr1[i][0] = arr[l+i][0];
		arr1[i][1] = arr[l+i][1];
	}

	for(j = 0; j < r-m; j++ )
	{
		arr2[j][0] = arr[j+m+1][0];
		arr2[j][1] = arr[j+m+1][1];
	}

	i = 0;
	j = 0;
	k = l;

	while((i < (m-l+1)) && (j < (r-m)))
	{
		if(arr1[i][1] < arr2[j][1]){
			arr[k][1] = arr1[i][1];
			arr[k][0] = arr1[i][0];
			inversions = (inversions + j)%1000000007;
			k++;
			i++;
		}

		else{
			arr[k][0] = arr2[j][0];
			arr[k][1] = arr2[j][1];
			k++;
			j++;
		}

	}

	while(i < (m-l+1)){
		arr[k][0] = arr1[i][0];
		arr[k][1] = arr1[i][1];
		k++;
		i++;
		inversions = (inversions + (j%1000000007))%1000000007;
	}
	while(j < (r-m)){
		arr[k][0] = arr2[j][0];
		arr[k][1] = arr2[j][1];
		k++;
		j++;
	}

	return inversions;

}

long long int inversion(double arr[100001][2], int l, int r)
{
	if(l < r)
	{
		int m = l + (r - l)/2;
		inversion(arr, l, m);
		inversion(arr, m+1, r);
		return mergei(arr, l, m, r);
	}
}

void merge(double arr[100001][2], int l, int m, int r)
{
	int i, j, k; 
	double arr1[m-l+1][2], arr2[r-m][2];

	for(i = 0; i < (m - l + 1); i++){
		arr1[i][0] = arr[l+i][0];
		arr1[i][1] = arr[l+i][1];
	}

	for(j = 0; j < r-m; j++){
		arr2[j][0] = arr[j+m+1][0];
		arr2[j][1] = arr[j+m+1][1];
	}

	i = 0;
	j = 0;
	k = l;

	while((i < (m-l+1)) && (j < (r-m)))
	{
		if((arr1[i][0] < arr2[j][0]) || fabs(arr1[i][0]-arr2[j][0])<0.0000001){
			if((fabs(arr1[i][0]- arr2[j][0])<0.0000001)&&(arr1[i][1] > arr2[j][1]))
			{
				arr[k][0] = arr2[j][0];
				arr[k][1] = arr2[j][1];
			}
			else
			{
				arr[k][0] = arr1[i][0];
				arr[k][1] = arr1[i][1];
			}
			i++;
			k++;
		}

		else{
			arr[k][0] = arr2[j][0];
			arr[k][1] = arr2[j][1];
			k++;
			j++;
		}
	}

	while(i < (m-l+1)){
		arr[k][0] = arr1[i][0];
		arr[k][1] = arr1[i][1];
		i++;
		k++;
	}
	while(j < (r-m)){
		arr[k][0] = arr2[j][0];
		arr[k][1] = arr2[j][1];
		j++;
		k++;
	}

	return;
}

void mergesort(double arr[100001][2], int l, int r)
{
	if(l < r)
	{
		int m = l + (r - l)/2;
		mergesort(arr, l, m);
		mergesort(arr, m+1, r);
		merge(arr, l, m, r);
	}
	return;
}


int main ()
{

	int n, i, j, k; 
	double l, r, a, b, c, arr[100001][2], arr1[100001];
	long long int answer;

	scanf("%d %lf %lf", &n, &l, &r);

	j = 0;
	k = 0;

	for(i = 0; i < n; i++){

		scanf("%lf %lf %lf", &a, &b, &c);

		if((fabs(b)> 0.0000001)){
			arr[k][0] = (-1*(a*l + c))/b;
			arr[k][1] = (-1*(a*r + c))/b;
			k++;
		}

		else if(((-1*c)/a  > l) && ((-1*c)/a < r))
			{
				arr1[j] = (-1*c)/a;
				j++;
			}
	}

	mergesort(arr, 0, k-1);

	answer = inversion(arr, 0, k-1)%1000000007;

	answer = (answer + (j*k)%1000000007)%1000000007;

	printf("%lld\n", answer);

	return 0;
}

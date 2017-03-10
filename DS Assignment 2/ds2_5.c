#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<limits.h>

typedef struct node{
	char name;
	int jumps;
	int visited;
	struct node * next;
}Node;

void bfs(Node arr[], Node alphabet[], int end)
{
	int temp, jump, temp3, i = 1;

	Node * temp2 = NULL;

	while(i <= end)
	{
		jump = arr[i].jumps + 1;

		temp = arr[i].name - 97;

		temp2 = alphabet[temp].next;

		if(alphabet[temp].visited == 0)
		{
			while(temp2 != NULL)
			{
				if(temp2 -> jumps > jump)
					temp2 -> jumps = jump;
				else
					break;
				temp2 = temp2 -> next;
			}
			alphabet[temp].visited = 1;
		}

		if(arr[i-1].jumps > jump)
		{
			arr[i-1].jumps = jump;
			temp3 = jump + 1;
			temp = arr[i-1].name - 97;
			temp2 = alphabet[temp].next;

				while(temp2 != NULL)
				{
					if(temp2 -> jumps > temp3)
						temp2 -> jumps = temp3;
					else
						break;
					temp2 = temp2 -> next;
				}
				alphabet[temp].visited = 1;
		}


		if(arr[i+1].jumps > jump)
		{
			arr[i+1].jumps = jump;
			temp3 = jump + 1;
			temp = arr[i+1].name - 97;
			temp2 = alphabet[temp].next;

				while(temp2 != NULL)
				{
					if(temp2 -> jumps > temp3)
						temp2 -> jumps = temp3;
					else
						break;
					temp2 = temp2 -> next;
				}
				alphabet[temp].visited = 1;
		}

		i++;
	}

	return;
}

int main ()
{

	int i, p, temp2;
	char temp[100001], building[100001];
	Node arr[100001], alphabet[26];
	Node * temp3 = NULL;

	for(i = 0; i < 100001; i++)
	{
		arr[i].next = NULL;
		if(i < 26)
		{
			alphabet[i].next = NULL;
			alphabet[i].visited = 0;
		}
	}

	scanf("%d", &p);

	for(i = -1; i < p; i++)
	{
		fgets(temp,100001,stdin);

		arr[i].name = temp[0];
		arr[i].jumps = INT_MAX;
		temp2 = temp[0] - 97;

		arr[i].next = alphabet[temp2].next;
		alphabet[temp2].next = &arr[i];
	}

	arr[1].jumps = 1;

	temp2 = arr[0].name - 97;

	temp3 = alphabet[temp2].next;

	while(temp3 != NULL)
	{
		temp3 -> jumps = 1;
		temp3 = temp3 -> next;
	}

	arr[0].jumps = 0;
	alphabet[temp2].visited = 1;

	if(arr[p-1].name != arr[0].name)
		bfs(arr, alphabet,  p-1);

	printf("%d\n", arr[p-1].jumps);

	return 0;
}

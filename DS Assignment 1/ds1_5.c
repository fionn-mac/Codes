#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct egg{
	int row;
	int column;
	int time;
	struct egg * next;
}Egg;

int main()
{
	int p, q, i, j, m, n, count, flag;
	char arr[1001][1001];

	Egg * head = (Egg *)malloc(sizeof(Egg));
	Egg * tail = NULL;
	Egg * temp = head;
	Egg * temp2 = head;
	Egg * temp3 = head;
	Egg * temp4 = head;

	scanf("%d", &p);

	for(q = 0; q < p; q++)
	{
		scanf("%d %d", &m, &n);
		count = 0;
		flag = 0;

		for(i = 0; i < m; i++)
			scanf("%s", arr[i]);

		for(i = 0; i < m; i++)
			for(j = 0; j < n; j++)
				if(arr[i][j] == 'r')
				{
					Egg * n = (Egg *)malloc(sizeof(Egg));
					n -> row = i;
					n -> column = j;
					n -> time = count;
					temp -> next = n;
					n -> next = tail;
					temp = n;
				}

		temp3 = temp;
		while(head -> next != tail)
		{
			temp2 = head->next;
			i = (temp2->row);
			j = (temp2->column);

			if((i+1 < m) && (j >= 0))
				if(arr[i+1][j] == 'f'){
					arr[i+1][j] = 'r';
					Egg * n = (Egg *)malloc(sizeof(Egg));
					n -> row = i+1;
					n -> column = j;
					n -> time = count;
					temp -> next = n;
					n -> next = tail;
					temp = n;
				}
			if((i-1 >= 0) && (j >= 0))
				if(arr[i-1][j] == 'f'){
					arr[i-1][j] = 'r';
					Egg * n = (Egg *)malloc(sizeof(Egg));
					n -> row = i-1;
					n -> column = j;
					n -> time = count;
					temp -> next = n;
					n -> next = tail;
					temp = n;
				}
			if((i >= 0) && (j-1 >= 0))
				if(arr[i][j-1] == 'f'){
					arr[i][j-1] = 'r';
					Egg * n = (Egg *)malloc(sizeof(Egg));
					n -> row = i;
					n -> column = j-1;
					n -> time = count;
					temp -> next = n;
					n -> next = tail;
					temp = n;
				}
			if((i >= 0) && (j+1 < n))
				if(arr[i][j+1] == 'f'){
					arr[i][j+1] = 'r';
					Egg * n = (Egg *)malloc(sizeof(Egg));
					n -> row = i;
					n -> column = j+1;
					n -> time = count;
					temp -> next = n;
					n -> next = tail;
					temp = n;
				}

			if(temp3 == temp2){
				count++;
				temp3 = temp;
			}
			temp2=head;
			head = head->next;
			free(temp2);
		}

		for(i = 0; i < m; i++){
			for(j = 0; j < n; j++)
				if(arr[i][j] == 'f'){
					printf("-1\n");
					flag = 1;
					break;
				}
			if(flag == 1)
				break;
		}
		if(flag == 0)
			printf("%d\n", count-1);
	}

	return 0;
}

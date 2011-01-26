#include<stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
	int **a,**b,**c;
	int x, y, r, i, j, k;
	//time_t t1, t2, t3;
	if(argc < 3)
	{
		printf("Too few parameters");
		return 1;
	}
	if (sscanf(argv[1], "%d", &x) == EOF || sscanf(argv[2], "%d", &y) == EOF || sscanf(argv[3], "%d", &r) == EOF)
	{
		printf("Bad parameter");
		return 2;
	}
	if(r<1)
	{
		printf("Too few repeats");
		return 3;
	}
	
	a = (int **)malloc(x * sizeof(int*));
	if (a == NULL)
	{
		printf("Memory allocation error");
		return 4;
	}
	b = (int **)malloc(x * sizeof(int*));
	if (b == NULL)
	{
		free(a);
		printf("Memory allocation error");
		return 4;
	}
	c = (int **)malloc(x * sizeof(int*));
	if (c == NULL)
	{
		free(a);
		free(b);
		printf("Memory allocation error");
		return 4;
	}
	
	a[0] = (int*)malloc(x * y * sizeof(int));
	b[0] = (int*)malloc(x * y * sizeof(int));
	c[0] = (int*)malloc(x * y * sizeof(int));
	if (a[0] == NULL||b[0] == NULL||c[0] == NULL) 
	{
		free(a);
		free(b);
		free(c);
		printf("Memory allocation error");
		return 4;
	}
	for (i = 1; i < x; i++) 
	{
		a[i] = a[0] + i * y;
		b[i] = b[0] + i * y;
		c[i] = c[0] + i * y;
	}
	for(k = 0; k < r; k++)
		for(i = 0; i < x; i++) 
			for(j = 0; j < y; j++)
				c[i][j] = a[i][j]*b[j][i];
	return 0;
}
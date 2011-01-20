#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define  MAX_SIZE_Y 5000
#define  MAX_SIZE_X 100

int main(int argc,char **argv)
{
	FILE *fout;
	int **matrix;
	int x, y, i, j, s = 0;
	time_t t1, t2, t3;
	if(argc < 3)
	{
		printf("Too few parameters");
		return 1;
	}
	if (sscanf(argv[1], "%d", &x) == EOF || sscanf(argv[2], "%d", &y) == EOF)
	{
		printf("Bad parameter");
		return 2;
	}
	fout = fopen(argv[3], "w");
	if(!fout)
	{
		printf("Can't open input file: %s", argv[3]);
		return 3;
	}
	
	matrix = (int **)malloc(x * sizeof(int*));
	if (matrix == NULL)
	{
		printf("Memory allocation error");
		return 4;
	}
	matrix[0] = (int*)malloc(x * y * sizeof(int));
	if (matrix[0] == NULL) 
	{
		free(matrix);
		printf("Memory allocation error");
		return 4;
	}
	for (i = 1; i < x; i++) 
	{
		matrix[i] = matrix[0] + i * y;
	}
	t1 = clock();
	for(i = 0; i < x; i++)  
		for(j = 0; j < y; j++ )
			s += matrix[i][j];  
	t2 = clock();
	for(i = 0; i < y; i++)  
		for(j = 0; j < x; j++)
			s += matrix[j][i];
	t3 = clock();
//results
    fprintf(fout, "Row-time: %d ms\nColumn-time: %d ms\nx = %d y = %d\n", (int)(t2-t1),(int)(t3-t2),x,y);
	fclose(fout);
	return 0;
}
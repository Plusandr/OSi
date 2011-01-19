#include <stdio.h>
#include <stdlib.h>

int compare (const void *a, const void *b);

int main(int argc, char **argv)
{
	FILE *in, *out;
	int i, err, input;
	int count=0;
	int *numbers=NULL;
	int *more_numbers=NULL;
	if(argc < 3)
	{
		printf("Too few parameters");
		return 1;
	}
	for(i=1;i<argc-1;i++)
	{
		in=fopen(argv[i],"r");
		if(!in)
		{
			printf("Can't open input file: %s",argv[i]);
			return 2;
		}
		while(!feof(in))
		{
			err=fscanf(in,"%d",&input);
			if(!err)
			{
				fclose(in);
				printf("Read error: %s",argv[i]);
				return 3;
			}
			count++;
			more_numbers = (int*) realloc (numbers, count * sizeof(int));
			if (more_numbers!=NULL) 
			{
				numbers=more_numbers;
				numbers[count-1]=input;
			}
			else
			{
				free (numbers);
				fclose(in);
				printf("Error (re)allocating memory");
				return 4;
			}
		}
	}
	qsort(numbers, count, sizeof(int),compare);
	out=fopen(argv[argc-1], "w");
	if(!out)
	{
        printf("Couldn't open output file: %s", argv[argc-1]);
		return 5;
	}
	for(i = 0;i < count; i++) 
	{
		err = fprintf(out, "%d\n", numbers[i]);
		if(!err)
		{
			fclose(out);
			printf("Couldn't write number to output file: %s",argv[argc-1]);
			return 6;
		}
	}
	free (numbers);
	return 0;
}
int compare (const void *a, const void *b)
{
     return *(int*)a - *(int*)b;
}
#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main()					//Gubenko Olesya 112
{
	int size, i, j, k, Error;
	double *A, *idA, *B;
	FILE *in, *out;
	printf("Hi! This program was made to compute the inverse matrix of given matrix A.\n");
	printf("Please, enter matrix size.\n");
	if ( (scanf("%d", &size) != 1) || (size < 0) )	{
		printf("Wrong matrix size, please, try again.\n");
		return -1;
	}

	//fscanf(in, "%d", &size);
	A = (double*) malloc(size * size * sizeof(double));
	idA = (double*) malloc(size * size * sizeof(double));
	B = (double*) malloc(size * size * sizeof(double));

	randomize(A, size);
	/*if (scan_matrix(in, A, size)==-1)
		printf("Not enough data in input.txt.\n");
		return -1;

	*/

	in = fopen("input.txt", "wt");
	print_matrix(in, A, size);
	fclose(in);

	copy(A, idA, size);
	identity(B, size);

	find_inverse(A, B, size, &Error);

	if (check(idA, B, size)==(-1))
		printf("Something went wrong while finding inverse matrix, please, try again.\nCheck the file 'check.txt' to see the result of A*B.\n");
	else {
		if (Error == 1)	{
			printf("There is no inverse matrix for non-square matrix.\n");
			return -1;
		}
		else {
			out = fopen("output.txt", "wt");
			printf("The inverse matrix was successfully found.\nCheck the file 'output.txt' to see the result.\nCheck the file 'check.txt' to see the result of A*B.\n");
			fprintf(out, "B: \n");
			print_matrix(out, B, size);
			fclose(out);
		}
	}
	free(A);
	free(idA);
	free(B);
	return 0;
}



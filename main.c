#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main()					//Gubenko Olesya 112
{
	int size, i, j, k, Error;
	double *A, *idA, *B;
	FILE *in = fopen("input.txt", "rt");
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
	/*
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			k = fscanf(in, "%lf", &A[i * size + j]);
			if (k != 1) {
				printf("Not enough data in input.txt.\n");
				return -1;
			}
		}
	}
	*/
	printf("Given matrix:\n");
	print_matrix(A, size);

	copy(A, idA, size);
	identity(B, size);
	find_inverse(A, B, size, &Error);

	if (check(idA, B, size)==(-1))
		printf("Something went wrong while finding inverse matrix, please, try again.\n");
	else {
		if (Error == 1)	{
			printf("There is no inverse matrix for non-square matrix.\n");
			return -1;
		}
		else {
			printf("The inverse matrix was successfully found:\n");
			print_matrix(B, size);
		}
	}
	free(A);
	free(idA);
	free(B);
	fclose(in);
	return 0;
}



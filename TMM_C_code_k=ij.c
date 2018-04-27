#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Turn 2D matrix index into 1D matrix index.
unsigned long long int idxLookup(unsigned long long int i, unsigned long long int j, int dimension) {
    return i * dimension + j;
} 

unsigned long long int multiplyMatrices(float *a, float *b, float *c, unsigned int triangular_matrix_size, unsigned int num_rows, unsigned int num_columns) {
	unsigned long long int aIndex = 0, bIndex = 0, cIndex = 0, num_ops = 0;
        // Multiply matrix elements from a and b, store in matrix c.
	for (unsigned int i = 0; i < num_rows; i++) {
	    for (unsigned int j = 0; j < num_columns; j++) {
  		cIndex = idxLookup(i, j, triangular_matrix_size);
		c[cIndex] = 0;
		for (unsigned int k = i; k < j+1; k++) {
		    //c[i][j] = a[i][j] * b[i][j];
		    aIndex = idxLookup(i, k, triangular_matrix_size);
		    bIndex = idxLookup(k, j, triangular_matrix_size);
		    c[cIndex] += a[aIndex] * b[bIndex];
		    num_ops += 2;
		} // end 3rd for
	    } // end 2nd for 
	} // end 1st for
	return num_ops;
} // end multiplyMatrices


int main() {
	// Program variables.
	unsigned int triangular_matrix_size = 0, num_rows = 0, num_columns = 0;
	unsigned long long int num_ops = 0;
	unsigned long long int index = 0; 
	char inputStr[128];
	
	// Prompt user for matrix size.
	printf("Enter size of triangular matrix: ");
	fgets(inputStr, 128, stdin);
	sscanf(inputStr, "%d", &triangular_matrix_size);
	//printf("Matrix size: %zd\n", triangular_matrix_size);
	
	// Calloc three triangular matrices based on size input with floats.
	float *a, *b, *c;
	printf("Calloc size: %d\n", triangular_matrix_size*triangular_matrix_size);
	a = calloc(triangular_matrix_size*triangular_matrix_size, sizeof(float));
	b = calloc(triangular_matrix_size*triangular_matrix_size, sizeof(float));
	c = calloc(triangular_matrix_size*triangular_matrix_size, sizeof(float));
	
	// Populate a and b triangular matrices with 1,2,3,...,matrix size. 
	for (unsigned int i = 0; i < triangular_matrix_size; i++) {
		for (unsigned int j = i; j < triangular_matrix_size; j++) {
			//a[i][j] = j + 1;
			//b[i][j] = j + 1;
			index = idxLookup(i, j, triangular_matrix_size);
			//num_ops += 2;
			a[index] = j + 1;
			b[index] = j + 1;
		} // end inner for	
	} // end outer for  
	
	/*
	// Print matrix a to verify element assignment.
	for (int i = 0; i < triangular_matrix_size; i++) {
		for (int j = 0; j < triangular_matrix_size; j++) {
		    index = idxLookup(i, j, triangular_matrix_size);
			printf("%f ", a[index]);
		} // end inner for	
		printf("\n");
	} // end outer for 
	printf("\n");
	*/
	
	// Start clock before multiplying matrices.
	clock_t begin = clock();
	
	num_rows = triangular_matrix_size;
	num_columns = triangular_matrix_size;
	num_ops = multiplyMatrices(a, b, c, triangular_matrix_size, num_rows, num_columns);
	
	// End clock and calculate time executing matrix multiplication.
	clock_t end = clock();
	double execution_time = (double) (end-begin)/CLOCKS_PER_SEC;
	
	/*
	// Print matrix c to verify element assignment.
	for (int i = 0; i < triangular_matrix_size; i++) {
		for (int j = 0; j < triangular_matrix_size; j++) {
		    index = idxLookup(i, j, triangular_matrix_size);
			printf("%f ", c[index]);
		} // end inner for	
		printf("\n");
	} // end outer for
	printf("\n");
	*/
	
	// Print statistics of TMM.
	printf("Computation time: %f\n", execution_time);
	printf("# Program Operations: %llu\n", num_ops);
	printf("FLOPs/sec: %f\n", num_ops/execution_time);
    free(a);
    free(b);
    free(c);	
	return 0;
} // end main





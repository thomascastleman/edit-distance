#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// get min of three integers
int min(int a, int b, int c) {
	int min = a < b ? a : b;	// get min of a and b
	return min < c ? min : c;	// get min of that and c
}

// calculate edit distance between two strings
int edit_dist(char source[], char target[]) {
	int sourceLen = strlen(source), targetLen = strlen(target);

	// check for empty strings
	if (sourceLen == 0 || targetLen == 0) {
		return sourceLen + targetLen;
	}

	int** matrix = malloc(sizeof(int *) * (targetLen + 1));	// allocate rows
	int r, c;	// row, col counters

	for (r = 0; r < targetLen + 1; r++) {
		// allocate columns
		*(matrix + r) = malloc(sizeof(int) * (sourceLen + 1));

		matrix[r][0] = r;	// init leftmost col values

		// init top row values
		if (r == 0) {
			for (c = 1; c < sourceLen + 1; c++) {
				matrix[r][c] = c;
			}
		}
	}

	// calculate all matrix values
	int cost;
	for (r = 1; r < targetLen + 1; r++) {
		for (c = 1; c < sourceLen + 1; c++) {
			cost = source[c - 1] == target[r - 1] ? 0 : 1;
			matrix[r][c] = min(
				matrix[r - 1][c] + 1,			// above element + 1
				matrix[r][c - 1] + 1, 			// left element + 1
				matrix[r - 1][c - 1] + cost		// northwest + cost
			);
		}
	}

	// debug log matrix
	for (r = 0; r < targetLen + 1; r++) {
		for (c = 0; c < sourceLen + 1; c++) {
			printf("%d ", matrix[r][c]);
		}
		printf("\n");
	}

	return matrix[targetLen][sourceLen];
}

void main() {

	char s[] = "convention";
	char t[] = "invention";

	printf("\nEdit distance \"%s\" \"%s\": %d\n", s, t, edit_dist(s, t));

}
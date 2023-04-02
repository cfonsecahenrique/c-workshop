/* 
 * File:  part1.c -> Pointers
 * Swap function
 * */

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
  int a = 5;
  int b = 10;
  printf("Before swapping: a=%d, b=%d\n", a, b);
  swap(&a, &b);
  printf("After swapping: a=%d, b=%d\n", a, b);
	return 0;
}


#include <stdio.h>
#include <stdlib.h>

int* generateArray(int size) {
  int * arr = (int *) malloc(sizeof(int) * 20);
  for(int i = 0; i < 20; i++) {
    arr[i] = i;
  }
  return arr;
}

int addArray(int* arr, int size) {
  int sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += i;
  }
  return sum;
}

int main() {
  int size = 20;
  int * arr = generateArray(size);
  printf("arr pointer = %p\n", arr);
  int sum = addArray(arr, size);
  printf("The array sum is: %d\n", sum);
  printf("The first value is: %d\n", *arr);
  printf("The second value is: %d\n", *(arr + 1));
  printf("The third value is: %d\n", *(arr + 2));
  printf("The fourth value is: %d\n", *(arr + 3));
  free(arr);
  printf("done!\n");
}

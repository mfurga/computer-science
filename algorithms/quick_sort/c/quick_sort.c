#include <stdio.h>

static int partition(int *arr, int lo, int hi)
{
  /* We'll take the first element in the array as our pivot. */
  int pivot = arr[lo];
  int tmp;

  int i = lo, j = hi + 1;
  while (1) {
    while (arr[++i] < pivot) if (i == hi) break;
    while (arr[--j] > pivot); /* if (j == lo) break; */

    if (j <= i) break;

    tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
  }

  tmp = arr[lo]; arr[lo] = arr[j]; arr[j] = tmp;
  return j;
}

static void quicksort_(int *arr, int lo, int hi)
{
  if (hi <= lo) return;
  int j = partition(arr, lo, hi);
  quicksort_(arr, lo, j - 1);
  quicksort_(arr, j + 1, hi);
}

void quicksort(int *arr, int size)
{
  return quicksort_(arr, 0, size - 1);
}
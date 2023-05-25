#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main()
{
    FILE *fp;
    int n;
    clock_t start_time = clock(); // start timer

    fp = fopen("input.txt", "r"); // Open the file for reading
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(fp, "%d", &n); // Read the length of the array from the file
    int arr[n];

    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &arr[i]); // Read the elements of the array from the file
    }

    fclose(fp); // Close the file

    quicksort(arr, 0, n - 1);
    clock_t end_time = clock(); // end timer

    double time_taken = ((double)(end_time - start_time) / CLOCKS_PER_SEC);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\nTime taken: %f seconds\n", time_taken);

    return 0;
}

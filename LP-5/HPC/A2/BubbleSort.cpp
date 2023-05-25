#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);

void bubble(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;

#pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void serial_bubble(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;

        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int &a, int &b)
{

    int test;
    test = a;
    a = b;
    b = test;
}

int main()
{

    int *a, *b, n;
    double start, stop, par_time, ser_time;
    cout << "\n enter total no of elements=>";
    cin >> n;
    a = new int[n];
    b = new int[n];
    cout << "\n enter elements=>";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }

    start = omp_get_wtime();
    bubble(a, n);
    stop = omp_get_wtime();
    par_time = stop - start;
    printf("\nParallel Time: %g\n", stop - start);

    start = omp_get_wtime();
    serial_bubble(a, n);
    stop = omp_get_wtime();
    par_time = stop - start;
    printf("\nSerial Time: %g\n", stop - start);

    string result;
    if (par_time > ser_time)
    {
        result = "Serial Faster";
    }
    else
    {
        result = "Parallel Faster";
    }
    cout << "\nTime Comparison: " << result << endl;

    cout << "\n sorted array is=>";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}
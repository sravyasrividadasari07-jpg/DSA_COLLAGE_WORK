#include <stdio.h>

int main(void)
{
    int a[100], n, i, j, key;
    int shifts = 0;

    printf("Enter number of marks: ");
    scanf("%d", &n);

    printf("Enter %d marks:\n", n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    // Insertion Sort
    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
            shifts++;
        }

        a[j + 1] = key;

        printf("After Pass %d: ", i);

        for (j = 0; j < n; j++)
        {
            printf("%d ", a[j]);
        }

        printf("\n");
    }

    printf("\nFinal Sorted Marks: ");

    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\nTotal Number of Shifts = %d\n", shifts);

    return 0;
}

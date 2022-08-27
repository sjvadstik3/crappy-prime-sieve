/*  Sjvadstik3's prime seive
    Copyright (C) 2022 sjvadstik3

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software Foundation, either version 3 of the License, or 
    (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
    even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see 
    <https://www.gnu.org/licenses/>. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define length 1000000000

//some stuff thay would have allowed to use an int array as a bit array
/*#define SetBit(A,k)     ( A[(k)/32] |= (1 << ((k)%32)) )
#define ClearBit(A,k)   ( A[(k)/32] &= ~(1 << ((k)%32)) )
#define TestBit(A,k)    ( A[(k)/32] & (1 << ((k)%32)) )*/

int *create_array(int *arr)
{
    int start[6] = {0, 1, 1, 0, 1, 0};
    int mid[6] = {1, 0, 0, 0, 1, 0};
    memcpy(arr, start, sizeof(start));
    int i;
    for (i = 12; i <= length; i = i + 6)
    {   
        memcpy(arr + (i - 6), mid, sizeof(mid));
    }
    i = i - 6;
    for (int j = 0; j < (length - i); j++)
    {   
        arr[i + j] = mid[j];
    }
    return arr;
}

int *seive(int *arr)
{
    int mesh = 5;
    int end = round(sqrt(length));
    while (mesh < end)
    {
        for (int i = mesh * mesh; i <= length; i = i + (mesh * 2))
        {
            arr[i - 1] = 0;
        }
        int next_prime = 0;
        while (next_prime == 0)
        {
            mesh = mesh + 2;
            if (mesh > end)
            {
                return arr;
            }
            if (arr[mesh - 1] == 1)
            {
                next_prime = 1;
            }
        }
    }
    return arr;
}

int main()
{
    static int a[length];
    int *b, *arr;
    b = create_array(a);
    arr = seive(b);
    int count = 0;
    FILE *fp;
    fp = fopen("prime.txt", "w");
    int i;
    for (i = 0; i < length; i++)
    {
        if (arr[i] == 1)
        {
            count ++;
            fprintf(fp, "%6d    %6d\n", count, i + 1);
        }
    }
    printf("%d primes found\n", count);
    fclose(fp);
    return 0;
}
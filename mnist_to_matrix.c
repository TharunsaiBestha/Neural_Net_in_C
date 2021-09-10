//#include "neural_network.c"
#include<string.h>
//#include<stdio.h>
char *itoa(int num, char *str)
{
    if (str == NULL)
    {
        return NULL;
    }
    sprintf(str, "%d", num);
    return str;
}
int *data_from_file(char *path)
{
    FILE *fptr;
    char c[2500];
    fptr = fopen(path, "r");
    if (fptr == NULL)
    {
        printf("no File");
    }
    fscanf(fptr, "%[^\n]", c);
    fclose(fptr);
    char *p = &c[0];
    int arr[790], ac = 0, s = 0;
    int *ptr = &arr[0];
    while (*p != 'E')
    {
        s = s * 10 + ((int)*p - 48);
        p++;
        if (*p == ' ')
        {
            p++;
            arr[ac] = s;
            s = 0;
            ac++;
        }
    }
    return ptr;
}
double *normalise(int *arr, int n)
{
    double *data = (double *)malloc(n * sizeof(double));
    *data = *arr;
    for (int i = 0; i < n; i++)
        *(data + i) = (double)(*(arr + i)) / 255.0;
    //free(arr);
    return data;
}
// Testing input function

double *image_input(int dig, int num, char ch)
{

    char path[100] = "/home/tharunsai/Documents/cfiles/matrices/mnist_in_text (2)/matrices/";
    if (ch == 'r')
        strcat(path, "train_data/");
    else if (ch == 'e')
        strcat(path, "test_data/");
    char digit[5];
    itoa(dig, digit);
    strcat(path, digit);
    strcat(path, "/");
    char numb[5];
    itoa(num, numb);
    strcat(path, numb);
    strcat(path, ".txt");

    //  "5/69.txt";
    int *data = data_from_file(path);
    // for (int i = 0; i < 785; i++)
    // {
    //     if (i % 28 == 1)
    //         printf("\n");
    //     printf("%d\t", *(data + i));
    // }
    // printf("\n");

    double *ndata = normalise(data, 785);
    // for (int i = 0; i < 785; i++)
    // {
    //     if (i % 28 == 1)
    //         printf("\n");
    //     if (*(ndata + i) != 0)
    //         printf("%.3f\t", *(ndata + i));
    //     else
    //         printf("0\t");
    // }
    // printf("\n");
    return ndata;
}


    //TESTING
//     for (int i = 0; i < 1; i++)
//     {
//         int dig = rand() % 10;
//         int num = rand() % trc[dig];

//         X = creat(784, 1);
//         Y = creat(10, 1);
        
//         temp = forward(X, W, 2, sigmoid);
//         backpropagation(Y, temp, W, 0.01, 2, sigmoid_grad);
//         destroy(X);
//     }
// }
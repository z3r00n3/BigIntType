#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

typedef struct bin{
    int length;
    int *num;
    char sign;
}big_int;

void read(big_int *ptr)
{
    char ch;

    while ((ch = getchar()) != '\n') {
        if (ch == '-'){
            ptr->sign = ch;
            ch = getchar();
        }
        ptr->num[ptr->length++] = ch - '0';
    }
}

void no_zero(big_int *ptr){
    int lgh = ptr->length;
    int j = 0;
    if(ptr->num[0] == 0 && ptr->length != 1){
        while(ptr->num[0] == 0 && j < lgh){
            for(int i = 0;i < ptr->length;i++){
                ptr->num[i] = ptr->num[i + 1];
            }
            ptr->length-=1;
            j++;
            if(ptr->num[0] == 0 && ptr->length == 1)
                break;
        }
    }
}

void inverse(big_int *ptr)
{
    int i;

    for (i = 0; i < (ptr->length / 2); i++)
    {
        char tmp;
        tmp = ptr->num[ptr->length - 1 - i];
        ptr->num[ptr->length - 1 - i] = ptr->num[i];
        ptr->num[i] = tmp;
    }
}

void increment(big_int *ptr)
{
    inverse(ptr);

    ptr->num[0] = ptr->num[0] + 1;
         int i = 0;
    for( i; i < (ptr->length - 1); i++){
        if(ptr->num[i] > 9){
            ptr->num[i] -= 10;
            ptr->num[i + 1] += 1;
        }

    }
    if(ptr->num[i] > 9){
        ptr->length +=1;
        ptr->num[i] -= 10;
        ptr->num[i + 1] = 1;

    }
    inverse(ptr);
    no_zero(ptr);
}

void init(big_int *ptr)
{
    ptr->num = (int *)calloc(SIZE, sizeof(int));
    ptr->length = 0;
    ptr->sign = '+';
}

void decrement(big_int *ptr)
{
    inverse(ptr);

    ptr->num[0] = ptr->num[0] - 1;
         int i = 0;
    for( i; i < ptr->length; i++){
        if(ptr->num[i] < 0){
            ptr->num[i] += 10;
            ptr->num[i + 1] -= 1;
        }
        inverse(ptr);
        no_zero(ptr);
    }
//    if(ptr->num[i + 1] == 0){
//        ptr->length -=1;
//        //ptr->num[i] += 10;
//        //ptr->num[i + 1] = 1;
//    }
}

int cmp_mod(big_int *ptr_A, big_int *ptr_B)
{
    if(ptr_A->length > ptr_B->length)
        return 1;
    if (ptr_A->length < ptr_B->length)
        return -1;
    if (ptr_A->length == ptr_B->length ) {
        int i = 0;
        while(ptr_A->num[i] == ptr_B->num[i] && i < ptr_A->length)
            i++;

        if (ptr_A->num[i] > ptr_B->num[i])
            return 1;
        if (ptr_A->num[i] < ptr_B->num[i])
            return -1;
        if (ptr_A->num[i] == ptr_B->num[i])
            return 0;
    }
}

void square (big_int *ptr_A,big_int *ptr_C)
{
    ptr_C->length = ptr_A->length + ptr_A->length;
    for(int i = 0;i < SIZE;i++){
            ptr_C->num[i] = 0;
        }
    ptr_C->sign = '+';
    inverse(ptr_A);
    for(int i = 0 ;i < ptr_A->length;i++)
    {
        for(int j = 0; j < ptr_A->length;j++){
            ptr_C->num[j + i] = ptr_C->num[j + i] + ptr_A->num[j] * ptr_A->num[i];
            if(ptr_C->num[j + i] > 9){
                ptr_C->num[j + i + 1] = ptr_C->num[j + i + 1] + ptr_C->num[j + i]/10;
                ptr_C->num[j + i] = ptr_C->num[j + i]%10;
            }
        }
    }
    inverse(ptr_C);
    inverse(ptr_A);
    no_zero(ptr_A);
    no_zero(ptr_C);
}

void square_div(big_int *ptr_A, big_int *ptr_C)
{
    big_int square_C;
    init(ptr_C);
    init(&square_C);
    ptr_C->length = 1;
    //square(ptr_C, &square_C);
    while (cmp_mod(ptr_A, &square_C) != -1) {
       init(&square_C);
       increment(ptr_C);
       square(ptr_C, &square_C);
    }
    decrement(ptr_C);
    //inverse(ptr_C);
}

void write(big_int *ptr)
{

        if (ptr->sign == '-')
            printf("-");

        for (int i = 0; i < ptr->length; i++)
            printf("%d", ptr->num[i]);
    }

int main(void)
{

    big_int A,C;
    init(&A);
    init(&C);
    read(&A);
    square_div(&A, &C);


    int i = 0;

//    while(C.num[i] == 0){
//        i++;
//    }
//    if(i >= 200)
//        printf("0");
//    else{
//        if(C.sign == '-'){
//    printf("%c", C.sign);
//    }
        while(i < C.length)
        {
            printf("%d", C.num[i]);
            i++;
        }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
This program find conjugate transpose of a complex matrix
*/

struct complex_number{
    float reel;
    float imaginer;
};

void show_complex_matrix(struct complex_number** matrix,int rowSize,int colSize);
void show_complex_matrix(struct complex_number** matrix,int rowSize,int colSize){
bool check = 0;
    for(int row = 0;row<rowSize;row++){
        putchar('|');

        for(int col =0;col<colSize;col++){
            if(matrix[col+row*colSize]->reel != 0)
                printf("%.2f",matrix[col+row*colSize]->reel);
            if(matrix[col+row*colSize]->reel == 0 && matrix[col+row*colSize]->imaginer == 0)
            {
                printf("0");
                if(col == colSize-1){
                    continue;
                }
                else{
                    printf(", ");
                }


            }
            else if(matrix[col+row*colSize]->reel == 0){
                check = 1;
            }

            if(matrix[col+row*colSize]->imaginer == 0){
                continue;
            }

            else if(matrix[col+row*colSize]->imaginer > 0){
                if(check = 1){
                    printf("+%.2fi",matrix[col+row*colSize]->imaginer);

                    if(col == colSize-1){
                        continue;
                    }
                    else{
                        printf(", ");
                    }
                }
                else{
                    printf("-%.2fi",matrix[col+row*colSize]->imaginer);
                    if(col == colSize-1){
                        continue;
                    }
                    else{
                        printf(", ");
                    }
                }

            }

            else{
                printf("%.2fi",matrix[col+row*colSize]->imaginer);
                if(col == colSize-1){
                    continue;
                }
                else{
                    printf(", ");
                }
            }

        }
        puts("|");
    }

}

struct complex_number **conjugate_transpose(struct complex_number** complex_mat,int rowSize,int colSize,int *rowSize_conjugate_transpose,int *colSize_conjugate_transpose);
struct complex_number **conjugate_transpose(struct complex_number** complex_mat,int rowSize,int colSize,int *rowSize_conjugate_transpose,int *colSize_conjugate_transpose){

    (*colSize_conjugate_transpose) = rowSize;
    (*rowSize_conjugate_transpose) = colSize;


    struct complex_number **conjugateTranspose = (struct complex_num **)malloc(sizeof(struct complex_num *)*rowSize*colSize);
    if(conjugateTranspose == NULL)
        return conjugateTranspose;
    for(int row = 0;row<rowSize;row++){
        for(int col=0;col<colSize;col++){
            conjugateTranspose[row+col*rowSize] = complex_mat[col+row*colSize];
            conjugateTranspose[row+col*rowSize]->imaginer *= -1;
        }
    }
    return conjugateTranspose;
}
int main()
{

    struct complex_number A00 = {3,7};
    struct complex_number A01 = {0,0};
    struct complex_number A10 = {0,2};
    struct complex_number A11 = {4,-1};
    /*
        Matrix:

        |3+7i, 0|
        |2i, 4-i|

        Conjugate transpose of a matrix :
        |3-7i, -2i|
        |0,    4+i|



    */

    int rowSize = 2;
    int colSize = 2;
    int conjugate_transpose_rowSize = colSize;
    int conjugate_transpose_colSize = rowSize;
    struct complex_number **matrix = (struct complex_number **)malloc(sizeof(struct complex_number*)*rowSize*colSize);
    matrix[0] = &A00;
    matrix[1] = &A01;
    matrix[2] = &A10;
    matrix[3] = &A11;

    puts("Matrix:");
    show_complex_matrix(matrix,rowSize,colSize);
    struct complex_number **conjugate_transpose_of_matrix = conjugate_transpose(matrix,rowSize,colSize,&conjugate_transpose_rowSize,&conjugate_transpose_colSize);
    if(conjugate_transpose_of_matrix == NULL){
        puts("Error!");
        exit(0);
    }

    puts("Conjugate transpose of matrix:");
    show_complex_matrix(conjugate_transpose_of_matrix,conjugate_transpose_rowSize,conjugate_transpose_colSize);


    return 0;
}



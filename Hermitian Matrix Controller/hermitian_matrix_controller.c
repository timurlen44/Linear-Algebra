#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    This program check a matrix is hermitian matrix or not.
*/

struct complex_number{
    float reel;
    float imaginer;
};

struct complex_number **conjugate_transpose(struct complex_number** complex_mat,int rowSize,int colSize,int *rowSize_conjugate_transpose,int *colSize_conjugate_transpose);
struct complex_number **conjugate_transpose(struct complex_number** complex_mat,int rowSize,int colSize,int *rowSize_conjugate_transpose,int *colSize_conjugate_transpose){

    (*colSize_conjugate_transpose) = rowSize;
    (*rowSize_conjugate_transpose) = colSize;


    struct complex_number **conjugateTranspose = (struct complex_num **)malloc(sizeof(struct complex_num *)*rowSize*colSize);
    if(conjugateTranspose == NULL)
        return conjugateTranspose;
    for(int row = 0;row<rowSize;row++){
        for(int col=0;col<colSize;col++){
            conjugateTranspose[row+col*rowSize] =  (struct complex_num **)malloc(sizeof(struct complex_num*));
            conjugateTranspose[row+col*rowSize]->imaginer = (-1)*complex_mat[col+row*colSize]->imaginer;
            conjugateTranspose[row+col*rowSize]->reel = complex_mat[col+row*colSize]->reel;
        }
    }
    return conjugateTranspose;
}

bool check_hermitian_matrix(struct complex_number** complex_mat,int rowSize,int colSize);
bool check_hermitian_matrix(struct complex_number** complex_mat,int rowSize,int colSize){
    if(rowSize != colSize)
        return false;

    int rowSize2;
    int colSize2;
    bool check = true;
    struct complex_number **conjugate_transpose_mat = conjugate_transpose(complex_mat,rowSize,colSize,&rowSize2,&colSize2);

    if(conjugate_transpose_mat == NULL)
        return false;

    for(int i = 0;i<rowSize*colSize; i++){
        if(conjugate_transpose_mat[i]->imaginer != complex_mat[i]->imaginer || conjugate_transpose_mat[i]->reel != complex_mat[i]->reel){
            check  = false;
            break;
        }
    }

    for(int i = 0;i< rowSize2*colSize2;i++){
        free(conjugate_transpose_mat[i]);
    }
    free(conjugate_transpose_mat);

    return check;
}
int main()
{

    struct complex_number A00 = { 1, 0};
    struct complex_number A01 = { 3,-1};
    struct complex_number A10 = { 3, 1};
    struct complex_number A11 = {-5, 0};


    /*
        Matrix:
        |1,   3-i|
        |3+i,  -5|

        Conjugate transpose of a matrix :
        |1,   3-i|
        |3+i,  -5|

        this matrix is hermitian matrix
*/

/*
        struct complex_number A00 = { 1, 0};
        struct complex_number A01 = { 3,-1};
        struct complex_number A10 = { 3, 1};
        struct complex_number A11 = {-5, -5i};


        Matrix:

        |1,   3-i|
        |3+i,  -5i|

        Conjugate transpose of a matrix :

        |1,   3-i|
        |3+i,  5i|

        this matrix is not hermitian matrix

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

    if(check_hermitian_matrix(matrix,rowSize,colSize) == true)
        puts("it is hermitian matrix");
    else
        puts("it is not hermitian matrix");

    free(matrix);



    return 0;
}



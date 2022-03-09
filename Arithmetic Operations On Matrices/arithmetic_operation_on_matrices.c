/*
    arithmetic operations on matrices
*/
#include<stdio.h>
#include<stdlib.h>

float *sum_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);
float *sum_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize){
    float *result = NULL;

    if(m1_rowSize != m2_rowSize || m1_colSize != m2_colSize)
        return NULL;

    result = (float *)malloc(sizeof(float)* m1_colSize*m1_rowSize);
    if(result == NULL)
        return NULL;

    for(int row = 0;row < m1_rowSize;row++){
        for(int col = 0;col < m1_colSize;col++){
                result[col+row*m1_colSize] = m1[col+row*m1_colSize] + m2[col+row*m1_colSize];
        }
    }

    return result;
}

float *substract_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);
float *substract_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize){
    float *result = NULL;

    if(m1_rowSize != m2_rowSize || m1_colSize != m2_colSize)
        return NULL;

    result = (float *)malloc(sizeof(float)* m1_colSize*m1_rowSize);
    if(result == NULL)
        return NULL;

    for(int row = 0;row < m1_rowSize;row++){
        for(int col = 0;col < m1_colSize;col++){
                result[col+row*m1_colSize] = m1[col+row*m1_colSize] - m2[col+row*m1_colSize];
        }
    }

    return result;
}

float *multiply_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);
float *multiply_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize){
    float *result = NULL;

    if(m1_colSize != m2_rowSize)
        return NULL;

    result = (float *)malloc(sizeof(float)* m1_rowSize*m2_colSize);
    if(result == NULL)
        return NULL;

    float sum = 0;
    for(int row1 = 0;row1<m1_rowSize;row1++){
        for(int col2=0;col2<m2_colSize;col2++){

            for(int k = 0;k < m1_colSize;k++){
                    sum += m1[k+row1*m1_colSize]*m2[col2+k*m2_colSize];
            }

            result[col2+row1*m1_rowSize] = sum;
            sum  = 0;

        }
    }

    return result;
}


void show_matrix(float *matrix, int rowSize, int colSize);
void show_matrix(float *matrix, int rowSize, int colSize){
    for(int row=0;row<rowSize;row++){
        putchar('|');
        for(int col=0;col<colSize;col++){
            printf("%.2f ",matrix[col+row*colSize]);
        }
        puts("|");
    }
}

int main(void){
    int rowSize = 3;
    int colSize = 3;
    float matrix1[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    float matrix2[3][3] = {{2,2,2},{2,2,2},{2,2,2}};
    float *sum = NULL;
    float *sub = NULL;
    float *mult = NULL;

    sum = sum_two_matrices(matrix1,matrix2,rowSize,colSize,rowSize,colSize);
    sub = substract_two_matrices(matrix1,matrix2,rowSize,colSize,rowSize,colSize);
    mult = multiply_two_matrices(matrix1,matrix2,rowSize,colSize,rowSize,colSize);


    if(sum == NULL){
        puts("Error");
        exit(1);
    }

    if(sub == NULL){
        puts("Error");
        exit(1);
    }

    if(mult == NULL){
        puts("Error");
        exit(1);
    }


    puts("Addition operation");
    puts("Matrix 1:");
    show_matrix(matrix1,rowSize,colSize);
    puts("Matrix 2:");
    show_matrix(matrix2,rowSize,colSize);
    puts("Sum of two matrices:");
    show_matrix(sum,rowSize,colSize);

    puts("----------------------------------------");

    puts("Subtraction operation");
    puts("Matrix 1:");
    show_matrix(matrix1,rowSize,colSize);
    puts("Matrix 2:");
    show_matrix(matrix2,rowSize,colSize);
    puts("Subtracting two matrices:");
    show_matrix(sub,rowSize,colSize);

    puts("----------------------------------------");

    puts("multiplication operation");
    puts("Matrix 1:");
    show_matrix(matrix1,rowSize,colSize);
    puts("Matrix 2:");
    show_matrix(matrix2,rowSize,colSize);
    puts("Multiplication of two matrices:");
    show_matrix(mult,rowSize,colSize);


    return 0;
}

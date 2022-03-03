#include<stdio.h>
#include<stdlib.h>
/*

This program find uppercase and lowercase triangular  matrices of a matrix

A = L*U

L = LOWER TRIANGULAR
U = UPPER TRIANGULAR

*/

float *upper_triangular(float *matrix,int Size);
float *upper_triangular(float *matrix,int Size){
    float *upper_triangular_mat = (float *)malloc(sizeof(float)*Size*Size);
    if(upper_triangular_mat == NULL)
        return NULL;

    for(int i =0;i<Size*Size;i++){
        upper_triangular_mat[i] = matrix[i];
    }
    float c = 0;//coefficient
    for(int row = 0 ;row<Size;row++){
        for(int row2 = row+1;row2<Size;row2++){
            c = upper_triangular_mat[row+row2*Size]/upper_triangular_mat[row+row*Size];
            for(int col = 0;col<Size;col++){
                upper_triangular_mat[col+row2*Size] -= upper_triangular_mat[col+row*Size]*c;
            }
        }
    }

    return upper_triangular_mat;
}

float *lower_triangular(float *matrix,int Size);
float *lower_triangular(float *matrix,int Size){
    float *lower_triangular_mat = (float *)malloc(sizeof(float)*Size*Size);
    if(lower_triangular_mat == NULL)
        return NULL;

    for(int i =0;i<Size*Size;i++){
        lower_triangular_mat[i] = matrix[i];
    }
    float c = 0;//coefficient
    for(int row = Size-1 ;row>=0;row--){
        for(int row2 = row-1;row2>=0;row2--){
            c = lower_triangular_mat[row+row2*Size]/lower_triangular_mat[row+row*Size];
            for(int col = Size-1;col>=0;col--){
                lower_triangular_mat[col+row2*Size] -= lower_triangular_mat[col+row*Size]*c;
            }
        }
    }

    return lower_triangular_mat;
}

void show_matrix(float *matrix,int rowSize, int colSize);
void show_matrix(float *matrix,int rowSize, int colSize){
    for(int row = 0;row<rowSize;row++){
        putchar('|');
        for(int col = 0;col<colSize;col++){
            printf("%.2f ",matrix[col+row*colSize]);
        }
        puts("|");
    }
    return;
}
int main(){
    puts("A = L*U");
    float matrix[2][2] = {{1,2},{3,4}};
    int Size = 2;
    float *upper_triangular_matrix = upper_triangular(matrix,Size);
    float *lower_triangular_matrix = lower_triangular(matrix,Size);

    if(upper_triangular_matrix == NULL){
        puts("Error!");
        exit(1);
    }

    if(lower_triangular_matrix == NULL){
        puts("Error!");
        exit(1);
    }
    puts("Matrix");
    show_matrix(matrix,Size,Size);
    puts("Lower triangular matrix");
    show_matrix(upper_triangular_matrix,Size,Size);
    puts("Upper triangular matrix");
    show_matrix(lower_triangular_matrix,Size,Size);

    free(upper_triangular_matrix);
    free(lower_triangular_matrix);

    return 0;
}

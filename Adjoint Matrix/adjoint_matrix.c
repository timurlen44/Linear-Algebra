#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
/*
This program show a matrix' transpose
*/
void showMatrix(float *mat, int rowSize,int colSize);
void showMatrix(float *mat, int rowSize,int colSize){
    for(int row = 0;row<rowSize;row++){
            putchar('|');
        for(int col =0;col<colSize;col++){
            printf("%.2f ",*(mat+col+row*colSize));
        }
        putchar('|');
        putchar('\n');
    }
}

bool row_and_col_controller(float *matrix,int Size);
bool row_and_col_controller(float *matrix,int Size){//if all of row is zero or all of column is zero then return false
    for(int row = 0;row<Size;row++){
        for(int col = 0;col<Size;col++){
            if(matrix[col+row*Size] != 0)
                break;
            if(col == Size-1)
                return false;
        }
    }


    for(int col = 0;col<Size;col++){
        for(int row = 0;row<Size;row++){
            if(matrix[col+row*Size] != 0)
                break;
            if(col == Size-1)
                return false;
        }
    }


    return true;
}

float *subtract_given_row_and_column_from_matrix(float *matrix,int Size,int row,int col);
float *subtract_given_row_and_column_from_matrix(float *matrix,int Size,int row,int col){
    float *new_matrix = (float *)malloc(sizeof(float)*(Size-1)*(Size-1));
    if(new_matrix == NULL)
        return NULL;

    int index = 0;
    for(int r = 0;r<Size;r++){
        for(int c = 0;c<Size;c++){
            if(r == row || c == col)
                continue;
            new_matrix[index++] = matrix[c+r*Size];
        }
    }
    return new_matrix;
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


float determinant_with_lower_triangular_matrix_method(float *matrix, int Size, bool *det_available);
float determinant_with_lower_triangular_matrix_method(float *matrix, int Size, bool *det_available){
    float det = 1;

    if(!row_and_col_controller(matrix,Size)){
        (*det_available) = false;
        return 0;
    }


    float *lower_triangular_mat = lower_triangular(matrix,Size);
    if(lower_triangular == NULL){
        (*det_available) = 0;
        return 0;
    }


    for(int i = 0;i<Size;i++){
        det *= lower_triangular_mat[i+i*Size];
    }

    (*det_available) = 1;
    return det;
}


float *Transpose(float *matrix,int Size);
float *Transpose(float *matrix,int Size){
    float* Transpose = (float *)malloc(sizeof(float)*Size*Size);

    if(!Transpose)
        return Transpose;

    for(int row = 0;row<Size;row++){
        for(int col =0;col<Size;col++){
            *(Transpose+row+col*Size) = *(matrix+col+row*Size);
        }
    }
    return Transpose;
}

float Cofactor(float *matrix,int Size,int row,int col);
float Cofactor(float *matrix,int Size,int row,int col){
    bool det_available;
    float cofactor = 0;
    float *subs_mat = subtract_given_row_and_column_from_matrix(matrix,Size,row,col);
    if(subs_mat != NULL){
        cofactor = pow(-1,row+col)*determinant_with_lower_triangular_matrix_method(subs_mat,Size-1,&det_available);
        free(subs_mat);
    }
    return cofactor;
}
float *Adjoint_Matrix(float *matrix, int Size);
float *Adjoint_Matrix(float *matrix, int Size){
    float *cofactor_mat = (float *)malloc(sizeof(float)*Size*Size);
    for(int row = 0; row<Size;row++){
        for(int col=0;col<Size;col++){
            cofactor_mat[col+row*Size] = Cofactor(matrix,Size,row,col);
        }
    }
    float *adjoint_mat = Transpose(cofactor_mat,Size);
    free(cofactor_mat);
    return adjoint_mat;
}

float *find_inverse_matrix_with_adjoint_matrix(float* matrix,int Size);
float *find_inverse_matrix_with_adjoint_matrix(float* matrix,int Size){
    bool det_available = false;
    float det = determinant_with_lower_triangular_matrix_method(matrix,Size,&det_available);
    if(det_available == false){
        return NULL;
    }

    float *inverse_mat = (float *)malloc(sizeof(float)*Size*Size);
    if(inverse_mat != NULL){
        for(int row = 0;row<Size;row++){
            for(int col = 0;col<Size;col++){
                inverse_mat[col+row*Size] = matrix[col+row*Size]/det;
            }
        }
    }

    return inverse_mat;
}


int main(){
    int Size = 2;
    float matrix[2][2]={
    {1,3},
    {2,5}
    };

    /*
    A = | 1  3 |
        | 2  5 |

    adjoint matrix:

    ADJ(A) = | 5 -3 |
             |-2  1 |

    A^-1 = |-5  3 |
           | 2 -1 |
    */
    float *adjoint_mat = Adjoint_Matrix(matrix,Size);
    if(adjoint_mat == NULL)
    {
        puts("Error!!!");
        exit(1);
    }
    float *inverse_mat = find_inverse_matrix_with_adjoint_matrix(adjoint_mat,Size);
    if(inverse_mat == NULL)
    {
        free(adjoint_mat);
        puts("Error!!!");
        exit(1);
    }

    puts("Matrix:");
    showMatrix(matrix,Size,Size);
    puts("Adjoint Matrix:");
    showMatrix(adjoint_mat,Size,Size);
    puts("Inverse Of Matrix:");
    showMatrix(inverse_mat,Size,Size);

    free(adjoint_mat);
    free(inverse_mat);
    return 0;
}




#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
/*
    This program will find determinant of a matrix
      |a 0 0|
  A = |b c 0|
      |d e f|

      det A = a * c * f

      |a b d|
  B = |0 c e|
      |0 0 f|

      det B = a * c * f

      |a 0 0|
  C = |0 c 0|
      |0 0 f|

      det C = a * c * f

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



bool det_available = 1;
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
float determinant_with_upper_triangular_matrix_method(float *matrix, int Size, bool *det_available);
float determinant_with_upper_triangular_matrix_method(float *matrix, int Size, bool *det_available){
    float det = 1;

    if(!row_and_col_controller(matrix,Size)){
        (*det_available) = false;
        return 0;
    }


    float *upper_triangular_mat = upper_triangular(matrix,Size);
    if(upper_triangular_mat == NULL){
        (*det_available) = 0;
        return 0;
    }


    for(int i = 0;i<Size;i++){
        det *= upper_triangular_mat[i+i*Size];
    }

    (*det_available) = 1;
    return det;
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

void show_matrix(float *matrix, int Size){

    for(int r = 0;r<Size;r++){
        putchar('|');
        for(int c = 0;c<Size;c++){
            printf("%.2f ",matrix[c+r*Size]);
        }
        puts("|");
    }


}


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


float determinant_with_cofactors_method(float *matrix, int Size, bool *det_available);
float determinant_with_cofactors_method(float *matrix, int Size, bool *det_available){
    float det = 0;

    if(!row_and_col_controller(matrix,Size)){
        (*det_available) = false;
        return 0;
    }

    (*det_available) =  true;
    if(Size == 1){
        return matrix[0];
    }

    else if(Size == 2){
        return matrix[0]*matrix[3]-matrix[1]*matrix[2];
    }
    else{
        float *element = NULL;
        for(int col = 0;col<Size;col++){
            
            element = subtract_given_row_and_column_from_matrix(matrix,Size,0,col);
            if(element != NULL){
                det += pow(-1,0+col)*matrix[col]*determinant_with_lower_triangular_matrix_method(element,Size-1,det_available);
                free(element);
            }
            else{
                (*det_available) = false;
                return 0;
            }
        }
    }
    return det;
}

int main(){
    float det_mat[3][3] = {
        {1,5,3},
        {2,4,7},
        {4,6,2}
        };


    int Size = 3;
    float det = 0;
    bool det_available_or_not = false;
    det = determinant_with_lower_triangular_matrix_method(det_mat,3,&det_available_or_not);
    if(!det_available_or_not){
        puts("determinant is not available for given matrix");
        exit(1);
    }
    else{
        printf("determinant with lower triangular matrix method = %.2f\n",det);
    }


    det = determinant_with_upper_triangular_matrix_method(det_mat,3,&det_available_or_not);
    if(!det_available_or_not){
        puts("determinant is not available for given matrix");
        exit(1);
    }
    else{
        printf("determinant with upper triangular matrix method = %.2f\n",det);
    }


    det = determinant_with_cofactors_method(det_mat,3,&det_available_or_not);
    if(!det_available_or_not){
        puts("determinant is not available for given matrix");
        exit(1);
    }
    else{
        printf("determinant with cofactor method = %.2f\n",det);
    }

}

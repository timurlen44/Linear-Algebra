#include<stdio.h>
#include<stdlib.h>
/*
    This program will find inverse of a matrix by using elementary operations.
    only the inverse of square matrices can be found
*/

float *create_identity_matrix(int size);
float *create_identity_matrix(int size){
    float *identity_mat = (float*)calloc(size*size,sizeof(float));
    for(int i = 0;i < size;i++)
        identity_mat[i+i*size] = 1;

    return identity_mat;
}

float *find_inverse_of_matrix(float *matrix,int size);
float *find_inverse_of_matrix(float *matrix,int size){
    float *inverse_mat = create_identity_matrix(size);
    if(inverse_mat == NULL)
        return NULL;
    float c = 0;//coefficient
    for(int row = 0;row<size;row++){
        c=matrix[row+row*size];
        for(int col = 0;col<size;col++){
            matrix[col+row*size] = matrix[col+row*size]/c;
            inverse_mat[col+row*size] = inverse_mat[col+row*size]/c;
        }


        for(int row2 = row+1;row2<size;row2++){
            c = matrix[row+size*row2]/matrix[row+size*row];
            for(int col2 = row;col2<size;col2++){
                matrix[col2+size*row2] -= c*matrix[col2+size*row];
                inverse_mat[col2+size*row2] -= c*inverse_mat[col2+size*row];
            }
        }
    }

    for(int row = size-1;row>=0;row--){

        for(int row2 = row-1;row2>=0;row2--){
            c = matrix[row+size*row2]/matrix[row+size*row];
            for(int col2 = row;col2>=0;col2--){
                matrix[col2+size*row2] -= c*matrix[col2+size*row];
                inverse_mat[col2+size*row2] -= c*inverse_mat[col2+size*row];
            }
        }
    }

    return inverse_mat;
}

void show_matrix(float *matrix,int rowSize, int colSize){

    for(int row = 0;row<rowSize;row++){
        putchar('|');
        for(int col = 0;col<colSize;col++){
            printf("%.2f ",matrix[col+row*colSize]);
        }
        puts("|");
    }

}

int main(){
    float matrix[2][2] = {{1,2},{3,4}};
    int size  = 2;

    puts("Matrix: ");
    show_matrix(matrix,size,size);

    float *inverse_mat = find_inverse_of_matrix(matrix,2);
    if(inverse_mat == NULL){
        puts("Error");
        exit(1);
    }

    puts("Inverse of matrix: ");
    show_matrix(inverse_mat,size,size);

    free(inverse_mat);

    return 0;
}

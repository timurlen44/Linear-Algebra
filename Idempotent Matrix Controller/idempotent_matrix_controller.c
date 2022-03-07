#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

float *multiply_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);
float *multiply_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize){
    float *result = NULL;

    if(m1_colSize != m2_rowSize)
        return NULL;

    result = (float *)malloc(sizeof(float)* m1_rowSize*m2_colSize);
    if(result == NULL)
        return NULL;
    int sum = 0;
    for(int row1 = 0;row1<m1_rowSize;row1++){
        for(int col2=0;col2<m2_rowSize;col2++){

            for(int k = 0;k < m1_colSize;k++){
                    sum += m1[k+row1*m1_colSize]*m2[col2+k*m2_rowSize];
            }
            result[col2+row1*m1_colSize] = sum;
            sum  = 0;

        }
    }

    return result;
}


bool check_idempotent_matrix(float *matrix,int rowSize, int colSize);
bool check_idempotent_matrix(float *matrix,int rowSize, int colSize){
    if(rowSize != colSize)//idempotent matrix have to be square matrix
        return false;

    float *result = multiply_two_matrices(matrix,matrix,rowSize,colSize,rowSize,colSize);
    if(result == NULL)
        return false;

    for(int i = 0;i<rowSize*colSize;i++){
        if(result[i] != matrix[i]){
            free(result);
            return false;
        }
    }
    free(result);
    return true;
}

int main(){
    int rowSize = 2;
    int colSize = 2;

    float matrix[2][2] = {{1,-1},{0,0}};
    //float matrix[2][2] = {{1,5},{7,9}};
    //float matrix[2][2] = {{1,0},{0,1}};


    if(check_idempotent_matrix(matrix,rowSize,colSize)){
        puts("it is idempotent matrix");
    }
    else{
        puts("it is not idempotent matrix");
    }


    return 0;
}

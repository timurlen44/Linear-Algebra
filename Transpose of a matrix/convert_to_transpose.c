#include<stdio.h>
#include<stdlib.h>
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

float *Transpose(float *matrix,int rowSize,int colSize,int *rowSizeTranspose,int *colSizeTranspose);
float *Transpose(float *matrix,int rowSize,int colSize,int *rowSizeTranspose,int *colSizeTranspose){
    *rowSizeTranspose = colSize;
    *colSizeTranspose = rowSize;
    float* Transpose = (float *)malloc(sizeof(float)*rowSize*colSize);

    if(!Transpose)
        return Transpose;

    for(int row = 0;row<rowSize;row++){
        for(int col =0;col<colSize;col++){
            *(Transpose+row+col*rowSize) = *(matrix+col+row*colSize);
        }
        putchar('\n');
    }
    return Transpose;
}

int main(){
    int rowSize = 2;
    int colSize = 3;
    int rowSizeTranspose = 0;
    int colSizeTranspose = 0;
    float matrix[2][3]= {{1,2,3},{4,5,6}};

    puts("Matrix");
    showMatrix(matrix,rowSize,colSize);
    float *Transpose_mat = Transpose(matrix,rowSize,colSize,&rowSizeTranspose,&colSizeTranspose);

    if (!Transpose)
    {
        puts("Transpose() func return NULL");
        exit(1);
    }

    puts("Transpose:");
    showMatrix(Transpose_mat,rowSizeTranspose,colSizeTranspose);
    free(Transpose);//We have to give back memory to OS
    return 0;
}




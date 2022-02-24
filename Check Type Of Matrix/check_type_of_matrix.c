#include<stdio.h>
#include<stdbool.h>
bool zeroMatrix(float *matrix,int rowSize,int colSize);
bool zeroMatrix(float *matrix,int rowSize,int colSize){
    for(int row=0;row<rowSize;row++){
        for(int col=0;col<colSize;col++){
            if(matrix[col+row*colSize] != 0)
                return 0;
        }
    }
    return 1;
}

bool diagonalMatrix(float *matrix,int rowSize,int colSize);
bool diagonalMatrix(float *matrix,int rowSize,int colSize){
    if(rowSize != colSize)
        return 0;
    for(int row = 0;row<rowSize;row++){
        for(int col = 0;col<colSize;col++){
            if(row == col)
                continue;
            if(matrix[col+row*colSize] != 0)
                return 0;
        }
    }
    return 1;
}

bool UpperTriAngularMatrix(float *matrix,int rowSize,int colSize);
bool UpperTriAngularMatrix(float *matrix,int rowSize,int colSize){
    if(rowSize != colSize)
        return 0;

    for(int row = 1;row<rowSize;row++){
        for(int col=row-1;col>=0;col--){

            if(matrix[col+row*colSize] != 0)
                return 0;

        }
    }
    return 1;
}

bool LowerTriAngularMatrix(float *matrix,int rowSize,int colSize);
bool LowerTriAngularMatrix(float *matrix,int rowSize,int colSize){
    if(rowSize != colSize)
        return 0;

    for(int row = 0;row<rowSize-1;row++){
        for(int col=row+1;col<colSize;col++){

            if(matrix[col+row*colSize] != 0)
                return 0;

        }
    }
    return 1;
}


bool identityMatrix(float *matrix,int rowSize,int colSize);
bool identityMatrix(float *matrix,int rowSize,int colSize){
    if(rowSize != colSize)
        return 0;

    for(int row = 0;row<rowSize-1;row++){
        for(int col=0;col<colSize;col++){
            if(row == col && matrix[col+row*colSize] != 1)
                return 0;
            else if(matrix[col+row*colSize] != 0)
                return 0;
        }
    }

    return 1;
}

bool symmetricMatrix(float *matrix,int rowSize,int colSize);
bool symmetricMatrix(float *matrix,int rowSize,int colSize){
    if(rowSize != colSize)
        return 0;

    for(int row = 0;row<rowSize-1;row++){
        for(int col=row+1;col<colSize;col++){
            if(row == col)
                continue;
            else if(matrix[col+row*colSize] != matrix[row+col*colSize])
                return 0;
        }
    }

    return 1;
}



int main(){

    float Z1[3] = {0,0,1};
    float Z2[3][2] = {{0,0},{0,0},{0,0}};
    printf("Z1 is %s\n",zeroMatrix(Z1,3,1)?"zero matrix.":"not zero matrix.");
    printf("Z2 is %s\n\n",zeroMatrix(Z2,3,2)?"zero matrix.":"not zero matrix.");

    float D1[3][3] = {{0,1,0},{1,1,1},{0,0,0}};
    float D2[2][2] = {{2,0},{0,2}};
    printf("D1 is %s\n",diagonalMatrix(D1,3,3)?"diagonal matrix.":"not diagonal matrix.");
    printf("D2 is %s\n\n",diagonalMatrix(D2,2,2)?"diagonal matrix.":"not diagonal matrix.");

    return 0;
}

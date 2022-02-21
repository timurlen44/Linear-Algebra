#include<stdio.h>
#include<stdbool.h>
/*
    Row Echelon Form Method:
    Program checking what arrays is row echelon form or not.

    Row Echelon Form Rules:

    1) The first element in a row other than 0 must be 1. This 1 is called the pivot element of that row.

    2) These pivots should be positioned to the right and bottom relative to the pivot of the previous row.

    3) The row with only 0's should be at the bottom.

    https://en.wikipedia.org/wiki/Row_echelon_form
*/
float arr[3][3] = {{1,2,3},{4,5,6},{7,8,5}};
bool check_zeros(float *arr,int colSize,int row);//This function checks what a row, is it all zero or not? if all of row is zero then return true else return false
bool check_zeros(float *arr,int colSize,int row){//collSize: How many columns does the array have?
    for(int i = 0;i<colSize;i++){
        if(arr[colSize*row+i] != 0)//equal to arr[row][i];
            return false;//the whole array is not zero.
    }
    return true;//the whole row is zero.
}

bool check_leading_ones(float* arr,int rowSize,int colSize);
bool check_leading_ones(float* arr,int rowSize,int colSize){
    int index = -1;
    for(int row = 0;row<rowSize;row++){
        for(int col = 0;col<colSize;col++){
            if(arr[row*colSize+col] != 0){//arr[row][col]
                if(arr[row*colSize+col] == 1)
                {
                    if(index<col){
                        index = col;
                        break;
                    }
                    else{
                        return 0;
                    }

                }
                else
                {
                    return 0;
                }

            }

        }
    }
    return 1;
}
bool check_echelon_form(float *arr,int rowSize,int colSize);
bool check_echelon_form(float *arr,int rowSize,int colSize){
    int counter = 0;//counts rows with all zero elements
    for(int row = rowSize-1;row>=0;row--){
        if(check_zeros(arr,colSize,row) != 1){
            counter++;
        }
        else{
            if(counter>0)
                return false;
        }
    }

    if(!check_leading_ones(arr,rowSize,colSize))
    {
        return false;
    }

    return true;
};
float arr1[3][3] = {
    {1,5,2},
    {0,1,4},
    {0,0,1}
};

float arr2[3][3] = {
    {1,-4,2},
    {0,0,1},
    {0,0,0}
};

float arr3[3][4] = {
    {1,4,4,2},
    {0,0,1,0},
    {1,0,0,0}
};

float arr4[3][4] = {
    {0,1,3,5},
    {0,0,1,2},
    {0,0,1,3}
};

float arr5[3][3] = {
    {2,4,5},
    {0,1,2},
    {0,0,1}
};
float arr6[3][3] = {
    {1,4,2},
    {0,0,0},
    {0,0,1}
};

float arr7[3][4] = {
    {1,3,5,6},
    {0,0,1,0},
    {0,1,0,0}
};

int main(){
    printf("arr1 is %s\n",check_echelon_form(arr1,3,3)?"row echelon form":"not row echelon form");
    printf("arr2 is %s\n",check_echelon_form(arr2,3,3)?"row echelon form":"not row echelon form");
    printf("arr3 is %s\n",check_echelon_form(arr3,3,4)?"row echelon form":"not row echelon form");
    printf("arr4 is %s\n",check_echelon_form(arr4,3,4)?"row echelon form":"not row echelon form");
    printf("arr5 is %s\n",check_echelon_form(arr5,3,3)?"row echelon form":"not row echelon form");
    printf("arr6 is %s\n",check_echelon_form(arr6,3,3)?"row echelon form":"not row echelon form");
    printf("arr7 is %s\n",check_echelon_form(arr7,3,4)?"row echelon form":"not row echelon form");
    return 0;
}


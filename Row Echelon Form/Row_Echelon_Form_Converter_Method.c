#include<stdio.h>
/*
This program converts a matrix to row echelon form.
*/

int check_zeros_in_row(float *arr,int colSize,int row);//This function checks what a row, is it all zero or not? if all of row is zero then return -1 else return the first element in a row other than 0
void swap_the_rows(float *coefficients_matrix,float *results_matrix,int colSize,int row_index,int index_zero_row);
void show_coefficients_matrix_and_result_matrix(float *coefficients_matrix,float *results_matrix,int rowSize,int colSize);
void row_echelon_form_converter(float *coefficients_matrix,float *results_matrix,int rowSize,int colSize);
void divide_the_row_by_the_given_number(float *coefficients_matrix,float *results_matrix,int colSize,int row_index,float given_number);

int check_zeros_in_row(float *arr,int colSize,int row){//collSize: How many columns does the array have?
    for(int i = 0;i<colSize;i++){
        if(arr[colSize*row+i] != 0)//equal to arr[row][i];
            return i;//the first element index in row other than 0
    }
    return -1;//the whole row is zero.
}

void swap_the_rows(float *coefficients_matrix,float *results_matrix,int colSize,int row_index,int index_zero_row){//The function swap the rows.
    float swap_value = 0;
    for(int col = 0;col<colSize;col++){
        swap_value = coefficients_matrix[col+row_index*colSize];
        coefficients_matrix[col+row_index*colSize] = coefficients_matrix[col+index_zero_row*colSize];
        coefficients_matrix[col+index_zero_row*colSize] = swap_value;
    }
    swap_value = results_matrix[row_index];
    results_matrix[row_index] = results_matrix[index_zero_row];
    results_matrix[index_zero_row] = swap_value;
    return;
}

void show_coefficients_matrix_and_result_matrix(float *coefficients_matrix,float *results_matrix,int rowSize,int colSize){
    for(int row = 0;row<rowSize;row++){
        for(int col = 0;col<colSize;col++){
            printf("%.1f ",coefficients_matrix[col+row*colSize]);
        }
        printf("|%.1f\n",results_matrix[row]);
    }
}

void divide_the_row_by_the_given_number(float *coefficients_matrix,float *results_matrix,int colSize,int row_index,float given_number){

    for(int col = 0;col<colSize;col++){
        coefficients_matrix[col+colSize*row_index] /= given_number;
    }
    results_matrix[row_index] /= given_number;

}


void row_echelon_form_converter(float *coefficients_matrix,float *results_matrix,int rowSize,int colSize){
    int index_zero_row = rowSize;
    int index_pivot = -1;
    int index = -1;
    for(int row = 0;row<index_zero_row;row++){
        index = check_zeros_in_row(coefficients_matrix,colSize,row);
        if(index == -1){
            swap_the_rows(coefficients_matrix,results_matrix,colSize,row,index_zero_row-1);
            index_zero_row--;
            row--;
            continue;
        }
        else{
            if(index>index_pivot){
                index_pivot = index;
                float coefficient = coefficients_matrix[index+colSize*row];
                if(coefficient != 1.0){
                    divide_the_row_by_the_given_number(coefficients_matrix,results_matrix,colSize,row,coefficient);
                }
                for(int row2 = row+1;row2<index_zero_row;row2++){
                    float coefficient = coefficients_matrix[index+colSize*row2]/coefficients_matrix[index+row*colSize];
                    for(int col2=index;col2<colSize;col2++){
                        coefficients_matrix[col2+colSize*row2] -= coefficient*coefficients_matrix[col2+colSize*row];
                    }
                    results_matrix[row2] -= coefficient*results_matrix[row];
                }

            }
            else{
                //Burayý sonra düþüneceksin...
            }
        }

    }

    return;
}
int main(){
    float c[3][4]={{1,-3,1,2},{2,-6,2,4},{1,-3,2,1}};
    float res_mat[3]={10,20,8};
    /*
        Matrix =>
        |1.0 -3.0 1.0 2.0| |A| |10.0|
        |2.0 -6.0 2.0 4.0|.|B|=|20.0|
        |1.0 -3.0 2.0 1.0| |C| | 8.0|
                           |D|

        Program convert the matrix to row echelon form =>
        |1.0 -3.0  1.0  2.0| |A| |10.0|
        |0.0  0.0  1.0 -1.0|.|B|=|-2.0|
        |0.0  0.0  0.0  0.0| |C| | 0.0|
                             |D|
    */
    puts("Matrix 1 row echelon form=>\n");
    row_echelon_form_converter(c,res_mat,3,4);
    show_coefficients_matrix_and_result_matrix(c,res_mat,3,4);
    puts("\n\n----------------------\n\n");




    float c2[3][3]={{2,-4,6},{1,3,-1},{3,-6,9}};
    float res_mat2[3]={10,5,15};
    /*
        Matrix =>
        |2.0 -4.0  6.0| |X| |10.0|
        |1.0  3.0 -1.0|.|Y|=| 5.0|
        |3.0 -6.0  9.0| |Z| |15.0|

        Program convert the matrix to row echelon form =>
        |1.0 -2.0  3.0| |X| |5.0|
        |0.0  1.0 -0.8|.|Y|=|0.0|
        |0.0  0.0  0.0| |Z| |0.0|




    */
    puts("Matrix 2 row echelon form=>\n");
    row_echelon_form_converter(c2,res_mat2,3,3);
    show_coefficients_matrix_and_result_matrix(c2,res_mat2,3,3);
    puts("\n\n----------------------\n\n");

    return 0;
}

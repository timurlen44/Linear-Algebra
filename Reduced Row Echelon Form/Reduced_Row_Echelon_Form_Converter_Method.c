#include<stdio.h>
/*
This program converts a matrix to reduced row echelon form.
*/
int check_zeros_in_row(float *arr,int colSize,int row);
void swap_the_rows(float *coefficients_matrix,float *results_matrix,int colSize,int row_index,int index_zero_row);
void show_coefficients_matrix_and_result_matrix(float *coefficients_matrix,float *results_matrix,int rowSize,int colSize);
void row_echelon_form_converter(float *coefficients_matrix,float *results_matrix,int rowSize,int colSize);
void divide_the_row_by_the_given_number(float *coefficients_matrix,float *results_matrix,int colSize,int row_index,float given_number);

int check_zeros_in_row(float *arr,int colSize,int row){
    for(int i = 0;i<colSize;i++){
        if(arr[colSize*row+i] != 0)
            return i;
    }
    return -1;
}

void swap_the_rows(float *coefficients_matrix,float *results_matrix,int colSize,int row_index,int index_zero_row){
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
        }

    }

    return;
}

void reduced_row_echelon_form_converter(float *coefficients_matrix,float *results_matrix,int rowSize,int colSize);
void reduced_row_echelon_form_converter(float *coefficients_matrix,float *results_matrix,int rowSize,int colSize){
    row_echelon_form_converter(coefficients_matrix,results_matrix,rowSize,colSize);
    int pivot_index = -1;
    float coefficient = 0;
    int adim = 0;
    for(int row = rowSize-1;row>=0;row--){
        pivot_index = check_zeros_in_row(coefficients_matrix,colSize,row);
        if(pivot_index != -1)
        {
            for(int row2=row-1;row2>=0;row2--){
                coefficient = coefficients_matrix[pivot_index+row2*colSize]/coefficients_matrix[pivot_index+row*colSize];
                for(int col2=pivot_index;col2<colSize;col2++){

                    coefficients_matrix[col2+row2*colSize] -= coefficient*coefficients_matrix[col2+row*colSize];
                }
                results_matrix[row2] -= results_matrix[row]*coefficient;
            }
        }

    }
    return;
}


int main(){
    float coef_mat[3][3]={{2,-4,6},{1,3,-1},{3,-6,9}};
    float res_mat[3]={10,5,15};

    /*
        Matrix =>
        |2.0 -4.0  6.0| |X| |10.0|
        |1.0  3.0 -1.0|.|Y|=| 5.0|
        |3.0 -6.0  9.0| |Z| |15.0|

        Row Echelon Form =>
        |1.0 -2.0  3.0| |X| |5.0|
        |0.0  1.0 -0.8|.|Y|=|0.0|
        |0.0  0.0  0.0| |Z| |0.0|

        Reduced Row Echelon Form =>
        |1.0  0.0  1.4| |X| |5.0|
        |0.0  1.0 -0.8|.|Y|=|0.0|
        |0.0  0.0  0.0| |Z| |0.0|
    */

    puts("Matrix reduced row echelon form=>\n");
    reduced_row_echelon_form_converter(coef_mat,res_mat,3,3);
    show_coefficients_matrix_and_result_matrix(coef_mat,res_mat,3,3);

    return 0;
}

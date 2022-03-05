#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void show_coefficients_matrix_and_result_matrix(int number_of_equations,float *coefficients_matrix,float *results_matrix);
void show_coefficients_matrix_and_result_matrix(int number_of_equations,float *coefficients_matrix,float *results_matrix){
    for(int i = 0;i<number_of_equations;i++){
        putchar('|');
        for(int y = 0;y<number_of_equations;y++){
            printf("%.1f ",coefficients_matrix[y+i*number_of_equations]);
        }
        printf("|%.1f\n",results_matrix[i]);
    }
}

void show_variables(int number_of_equations,float *variables_matrix);
void show_variables(int number_of_equations,float *variables_matrix){
    for(int x=0;x<number_of_equations;x++){
        printf("%c = %.2f\n",65+x,variables_matrix[x]);//65 is 'A' in ASCII table, 65+0 = 'A' ,65+1 = 'B' ,65+2 = 'C'.
    }
}


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


float determinant_with_upper_triangular_matrix_method(float *matrix, int Size, bool *det_available);
float determinant_with_upper_triangular_matrix_method(float *matrix, int Size, bool *det_available){
    float det = 1;

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


void copy_mat(float *coefficients_matrix, float*results_matrix,float *new_mat, int Size,int col_index);
void copy_mat(float *coefficients_matrix, float*results_matrix,float *new_mat, int Size,int col_index){
    if(new_mat == NULL)
        return;

    for(int col = 0;col<Size;col++){
        for(int row = 0;row<Size;row++){
            if(col != col_index){
                new_mat[col+row*Size] = coefficients_matrix[col+row*Size];
            }
            else{
                new_mat[col+row*Size] = results_matrix[row];
            }

        }
    }
    return;
}

float *cramer_method(float *coefficients_matrix,float *results_matrix, int Size);
float *cramer_method(float *coefficients_matrix,float *results_matrix, int Size){
    float* variables_mat = (float *)malloc(sizeof(float)*Size);//variables_mat[0] = X = 17.7 ,variables_mat[1] = Y = 2.33 , variables_mat[2] = Z = 9.99
    float *new_mat = (float *)malloc(sizeof(float)*Size*Size);
    bool det_available1 = true;
    bool det_available2 = true;
    for(int i = 0;i<Size;i++){
        copy_mat(coefficients_matrix,results_matrix,new_mat,Size,i);
        variables_mat[i] = determinant_with_upper_triangular_matrix_method(new_mat,Size,&det_available1)/determinant_with_upper_triangular_matrix_method(coefficients_matrix,Size,&det_available2);

        if(det_available1 == false || det_available2 == false){
            free(new_mat);
            free(variables_mat);
            return NULL;
        }

    }

    free(new_mat);
    return variables_mat;
}


int main(void){
    int Size = 2;
    float coeffition_mat[2][2] = {{-1,-2},{-3, 1}};
    float result_mat[2] = {1,0};
    float *variables_mat = NULL;//A = 5 , B= 1.33 , C = 9,66

    /*
    A = |-1 -2| |A| = |1|
        |-3 +1|.|B|   |0|

    A = -1/7 = -0.14
    B = -3/7 = -0.43
    */

    variables_mat = cramer_method(coeffition_mat,result_mat,Size);

    if(variables_mat == NULL){
        puts("Error!");
        exit(1);
    }
    show_coefficients_matrix_and_result_matrix(Size,coeffition_mat,result_mat);
    show_variables(Size,variables_mat);

    free(variables_mat);



    return 0;
}



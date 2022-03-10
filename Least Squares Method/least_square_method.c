#include<stdio.h>
#include<stdlib.h>
void gauss_elemination_method(int number_of_equations,float *coefficients_matrix, float *results_matrix, float *variables_matrix);
void show_coefficients_matrix_and_result_matrix(int number_of_equations,float *coefficients_matrix,float *results_matrix);
void show_variables(int number_of_equations,float *variables_matrix);
float *Transpose(float *matrix,int rowSize,int colSize,int *rowSizeTranspose,int *colSizeTranspose);
float *sum_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);
float *multiply_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);
float *substract_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);




float *sum_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);
float *sum_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize){
    float *result = NULL;

    if(m1_rowSize != m2_rowSize || m1_colSize != m2_colSize)
        return NULL;

    result = (float *)malloc(sizeof(float)* m1_colSize*m1_rowSize);
    if(result == NULL)
        return NULL;

    for(int row = 0;row < m1_rowSize;row++){
        for(int col = 0;col < m1_colSize;col++){
                result[col+row*m1_colSize] = m1[col+row*m1_colSize] + m2[col+row*m1_colSize];
        }
    }

    return result;
}

float *substract_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);
float *substract_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize){
    float *result = NULL;

    if(m1_rowSize != m2_rowSize || m1_colSize != m2_colSize)
        return NULL;

    result = (float *)malloc(sizeof(float)* m1_colSize*m1_rowSize);
    if(result == NULL)
        return NULL;

    for(int row = 0;row < m1_rowSize;row++){
        for(int col = 0;col < m1_colSize;col++){
                result[col+row*m1_colSize] = m1[col+row*m1_colSize] - m2[col+row*m1_colSize];
        }
    }

    return result;
}
float *multiply_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize);
float *multiply_two_matrices(float *m1,float *m2, int m1_rowSize, int m1_colSize ,int m2_rowSize, int m2_colSize){
    float *result = NULL;

    if(m1_colSize != m2_rowSize)
        return NULL;

    result = (float *)malloc(sizeof(float)* m1_rowSize*m2_colSize);
    if(result == NULL)
        return NULL;
    float sum = 0;
    for(int row1 = 0;row1<m1_rowSize;row1++){
        for(int col2=0;col2<m2_colSize;col2++){

            for(int k = 0;k < m1_colSize;k++){
                    sum += m1[k+row1*m1_colSize]*m2[col2+k*m2_colSize];
            }
            result[col2+row1*m2_colSize] = sum;
            sum  = 0;

        }
    }

    return result;
}





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

void gauss_elemination_method(int number_of_equations,float *coefficients_matrix, float *results_matrix, float *variables_matrix){
    for(int y = 0;y<number_of_equations;y++){
        for(int x = y+1;x<number_of_equations;x++){
            float multiplication_coefficient = (*(coefficients_matrix + y + x*number_of_equations))/(*(coefficients_matrix + y + y*number_of_equations));
            for(int k = y;k<number_of_equations;k++){//coefficients_matrix is modifying
                *(coefficients_matrix + k + x*number_of_equations) -= *(coefficients_matrix + k + y*number_of_equations)*multiplication_coefficient;
            }
            results_matrix[x] -= results_matrix[y]*multiplication_coefficient;
        }
    }

    for(int x=number_of_equations-1;x>=0;x--){
        float res = results_matrix[x];
        for(int y = x+1;y<number_of_equations;y++){

            res -= variables_matrix[y]*coefficients_matrix[y+x*number_of_equations];
        }
        variables_matrix[x] = res/coefficients_matrix[x+x*number_of_equations];
    }
    return;
}

void show_coefficients_matrix_and_result_matrix(int number_of_equations,float *coefficients_matrix,float *results_matrix){
    for(int i = 0;i<number_of_equations;i++){
        for(int y = 0;y<number_of_equations;y++){
            printf("%.1f ",coefficients_matrix[y+i*number_of_equations]);
        }
        printf("|%.1f\n",results_matrix[i]);
    }
}

void show_variables(int number_of_equations,float *variables_matrix){
    for(int x=0;x<number_of_equations;x++){
        printf("X%d = %.2f\n",x+1,variables_matrix[x]);//65 is 'A' in ASCII table, 65+0 = 'A' ,65+1 = 'B' ,65+2 = 'C'.
    }
}

void show_vector(int vectorSize, float *vector);
void show_vector(int vectorSize, float *vector){
    putchar('(');
    for(int i = 0;i<vectorSize;i++){
        printf("%.2f",vector[i]);
        if(i != vectorSize-1){
            printf(", ");
        }

    }
    puts(")");

}


float *least_squares_method_variables_vector(float *coefficients_matrix, float *results_matrix, int rowSize, int colSize);
float *least_squares_method_variables_vector(float *coefficients_matrix, float *results_matrix, int rowSize, int colSize){
    int colSizeTranspose;
    int rowSizeTranspose;
    int rowSizeResults;
    float *transpose = Transpose(coefficients_matrix,rowSize,colSize,&rowSizeTranspose,&colSizeTranspose);

    if(transpose == NULL)
        return NULL;

    float *new_coef = multiply_two_matrices(transpose, coefficients_matrix,rowSizeTranspose,colSizeTranspose,rowSize,colSize);
    if(new_coef == NULL)
        return NULL;

    float *new_res = multiply_two_matrices(transpose, results_matrix,rowSizeTranspose,colSizeTranspose,rowSize,1);
    if(new_res == NULL)
        return NULL;
    float * variables_matrix = (float *)malloc(sizeof(float)*colSize);
    if(variables_matrix == NULL)
        return NULL;

    gauss_elemination_method(rowSizeTranspose,new_coef,new_res,variables_matrix);
    return variables_matrix;
}

float *least_squares_method_error_vector(float *coefficients_matrix, float *results_matrix, float *variables_matrix, int rowSize, int colSize);
float *least_squares_method_error_vector(float *coefficients_matrix, float *results_matrix, float *variables_matrix, int rowSize, int colSize){
    float *error_vector = (float *)malloc(sizeof(float)*rowSize);
    if(error_vector == NULL)
        return NULL;

    float *A_and_X_multiply =  multiply_two_matrices(coefficients_matrix,variables_matrix,rowSize,colSize,colSize,1);
    if(A_and_X_multiply == NULL)
        return NULL;

    error_vector = substract_two_matrices(results_matrix,A_and_X_multiply,rowSize,1,rowSize,1);

    return error_vector;
}

float least_squares_method_total_error(int error_vector_size, float *error_vector);
float least_squares_method_total_error(int error_vector_size, float *error_vector){
    float error = 0;
    for(int i = 0;i<error_vector_size;i++){
        error += powf(error_vector[i],2.0);
    }
    return sqrtf(error);

}

int main(){
    int colSize = 2;
    int rowSize = 3;
    float coefficients_matrix[3][2] = {{ 1,-1},{ 3, 2},{-2, 4}};
    float results_matrix[3]={4,1,3};
    /*
    | 1 -1| |X1|   |4|
    | 3  2|.|X2| = |1|
    |-2  4|        |3|

    least squares method

    approximately X1 = 0.18
    approximately X2 = 0.50

    Error Vector:
    (4.32, -0.54, 1.35)

    Total Error: 4.56
    */

    float *variables_vector = NULL;
    float *error_vector = NULL;
    variables_vector = least_squares_method_variables_vector(coefficients_matrix,results_matrix,rowSize,colSize);
    show_variables(colSize,variables_vector);

    error_vector = least_squares_method_error_vector(coefficients_matrix,results_matrix,variables_vector,rowSize,colSize);
    puts("Error vector: ");
    show_vector(rowSize,error_vector);

    printf("Total Error: %.2f",least_squares_method_total_error(rowSize,error_vector));

    free(error_vector);
    free(variables_vector);

    return 0;
}



#include<stdio.h>
#include<stdlib.h>
void gauss_elemination_method(int number_of_equations,float *coefficients_matrix, float *results_matrix, float *variables_matrix);
void show_coefficients_matrix_and_result_matrix(int number_of_equations,float *coefficients_matrix,float *results_matrix);
void show_variables(int number_of_equations,float *variables_matrix);


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
        printf("%c = %.2f\n",65+x,variables_matrix[x]);//65 is 'A' in ASCII table, 65+0 = 'A' ,65+1 = 'B' ,65+2 = 'C'.
    }
}
int main(){
    float coefficients_matrix[3][3] = {{1,2,3},{4,5,6},{7,8,5}};
    float results_matrix[3]={14,32,38};
    float variables_matrix[3]={0,0,0};
    /*

    A = 0
    B = 0
    C = 0

    |1 2 3| |A|   |14|
    |4 5 6|.|B| = |32|
    |7 8 5| |C|   |38|
    */
    puts("Show coefficients matrix and results matrix");
    show_coefficients_matrix_and_result_matrix(3,coefficients_matrix,results_matrix);
    /*

    |1 2 3| |A|   |14|
    |4 5 6|.|B| = |32|
    |7 8 5| |C|   |38|

    */
    gauss_elemination_method(3,coefficients_matrix,results_matrix,variables_matrix);



    puts("\n\nShow upper triangular coefficients matrix and results matrix");
    show_coefficients_matrix_and_result_matrix(3,coefficients_matrix,results_matrix);
    /*
        |1  2  3| |A|  | 14|
        |0 -3 -6|.|B|= |-24|
        |0  0 -4| |C|  |-12|
    */
    puts("\n\nShow variables");
    show_variables(3,variables_matrix);

    /*
        A = 1
        B = 2
        C = 3
    */
    //variables_matrix[0] = A,  variables_matrix[1] = B,  variables_matrix[2] = C
    return 0;
}


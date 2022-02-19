#include<stdio.h>
#include<stdbool.h>//For using true and false statements
void show_matrix(int number_of_equations,float *coefficients_matrix,float *results_matrix);
void gauss_jordan_elemination_method(int number_of_equations,float *coefficients_matrix, float *results_matrix, float *variables_matrix,bool show);
void show_variables(int number_of_equations,float *variables_matrix);

void show_matrix(int number_of_equations,float *coefficients_matrix,float *results_matrix){
    for(int x = 0;x<number_of_equations;x++){
        for(int k=0;k<number_of_equations;k++){
            printf("%.2f ",coefficients_matrix[x*number_of_equations+k]);
        }
        printf("|%.2f| \n",results_matrix[x]);
    }

}

void gauss_jordan_elemination_method(int number_of_equations,float *coefficients_matrix, float *results_matrix, float *variables_matrix,bool show){
    for(int y=0;y<number_of_equations;y++){
        for(int x=y+1;x<number_of_equations;x++){
            float multiplication_coefficient = coefficients_matrix[x*number_of_equations+y]/coefficients_matrix[y*number_of_equations+y];
            for(int k=y;k<number_of_equations;k++){
                    coefficients_matrix[x*number_of_equations+k] -= coefficients_matrix[y*number_of_equations+k]*multiplication_coefficient;
            }
            results_matrix[x] -= results_matrix[y]*multiplication_coefficient;
        }
    }
    ////////////////////////////////////////////////////////////////////////////
    /*
        print matrix
        STEP1:
    */
    if(show){
        puts("STEP1:");
        show_matrix(number_of_equations,coefficients_matrix,results_matrix);
    }
    ////////////////////////////////////////////////////////////////////////////

    for(int x = number_of_equations-1;x>=0;x--){
        float quotient_coefficient = coefficients_matrix[x*number_of_equations+x];
        for(int k=x;k<number_of_equations;k++){
            coefficients_matrix[x*number_of_equations+k] /= quotient_coefficient;
        }
            results_matrix[x] /= quotient_coefficient;

    }

    ////////////////////////////////////////////////////////////////////////////
    /*
        print matrix
        STEP2:
    */
    if(show){
        puts("\n\nSTEP2:");
        show_matrix(number_of_equations,coefficients_matrix,results_matrix);
    }

    ////////////////////////////////////////////////////////////////////////////

    for(int y=number_of_equations;y>=0;y--){
        for(int x=y-1;x>=0;x--){
            float multiplication_coefficient = coefficients_matrix[x*number_of_equations+y]/coefficients_matrix[y*number_of_equations+y];
            for(int k=y;k<number_of_equations;k++){
                    coefficients_matrix[x*number_of_equations+k] -= coefficients_matrix[y*number_of_equations+k]*multiplication_coefficient;
            }
            results_matrix[x] -= results_matrix[y]*multiplication_coefficient;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    /*
        print matrix
        STEP3:
    */
    if(show){
        puts("\n\nSTEP3:");
        show_matrix(number_of_equations,coefficients_matrix,results_matrix);
        putchar('\n');
    }
    ////////////////////////////////////////////////////////////////////////////
    for(int x = 0;x<number_of_equations;x++){
        variables_matrix[x] = results_matrix[x];
    }


}

void show_variables(int number_of_equations,float *variables_matrix){
    for(int x=0;x<number_of_equations;x++){
        printf("%c = %.2f\n",65+x,variables_matrix[x]);//65 is 'A' in ASCII table, 65+0 = 'A' ,65+1 = 'B' ,65+2 = 'C'.
    }
}


int main(void){
    bool show = true;//if turn to false program will not show algorithm steps
    float coefficients_matrix[3][3] = {{1,2,3},{4,5,6},{7,8,5}};
    float results_matrix[3]={14,32,38};
    float variables_matrix[3]={0,0,0};
    int number_of_equations = 3;
    /*
    A+2B+3C  = 14
    4A+5B+6C = 32
    7A+8B+5C = 38

    |1 2 3| |X|  |14|
    |4 5 6|.|Y|= |32|
    |7 8 5| |Z|  |38|

    STEP1:
    |1  2  3| |X|  | 14|
    |0 -3 -6|.|Y|= |-24|
    |0  0 -4| |Z|  |-12|

    STEP2:
    |1 2 3| |X|  |14|
    |0 1 2|.|Y|= | 8|
    |0 0 1| |Z|  | 3|

    STEP3:
    |1 0 0| |X|  |1|
    |0 1 0|.|Y|= |2|
    |0 0 1| |Z|  |3|

    X=1
    Y=2
    Z=3

    */

    gauss_jordan_elemination_method(number_of_equations, coefficients_matrix, results_matrix, variables_matrix,show);
    show_variables(number_of_equations,variables_matrix);
}


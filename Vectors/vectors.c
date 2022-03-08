#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<math.h>

float dot_product(float *vector1,float *vector2,int8_t dimension);
float dot_product(float *vector1,float *vector2,int8_t dimension){
    float result  = 0;
    for(int8_t i = 0; i<dimension;i++){
        result += vector1[i]*vector2[i];
    }
    return result;
}

float vector_length(float *vector,int8_t dimension);
float vector_length(float *vector,int8_t dimension){
    float length = 0;
    for(int8_t i = 0;i<dimension; i++){

        length += powf(vector[i],2);
    }
    //printf("nedir = %f\n",length);
    return sqrt(length);
}

float angle_between_vectors(float *vector1,float *vector2,int8_t dimension);
float angle_between_vectors(float *vector1,float *vector2,int8_t dimension){
    return ((dot_product(vector1,vector2,dimension))/(powf(vector_length(vector1,dimension),2)));
}

float *vector_projection(float *vector1, float *vector2, int8_t dimension);
float *vector_projection(float *vector1, float *vector2, int8_t dimension){
    float *new_vector = (float *)malloc(sizeof(float)*dimension);
    float quotient_coefficient = (dot_product(vector1,vector2,dimension)/powf(vector_length(vector2,dimension),2));
    for(int8_t i = 0;i<dimension;i++){
        new_vector[i] = vector2[i] * quotient_coefficient;
    }
    return new_vector;
}

void print_vector(float *vector, int8_t dimension);
void print_vector(float *vector, int8_t dimension){
    printf("vector = (");
    for(int8_t i = 0;i<dimension; i++){
        printf("%.2f",vector[i]);
        if(i != dimension-1){
            putchar(', ');
        }
    }
    puts(")");

}

float *cross_product(float *vector1, float *vector2, int8_t dimension);
float *cross_product(float *vector1, float *vector2, int8_t dimension){
    float *result = (float *)malloc(sizeof(float)*dimension);
    if(result == NULL){
        return NULL;
    }
    //Rule of Sarrus
    result[0] = vector1[1]*vector2[2] - vector1[2]*vector2[1];
    result[1] = vector2[0]*vector1[2] - vector2[2]*vector1[0];
    result[2] = vector1[0]*vector2[1] - vector1[1]*vector2[0];
    return result;

}

bool check_for_parallel_vectors(float *vector1, float *vector2, int8_t dimension);
bool check_for_parallel_vectors(float *vector1, float *vector2, int8_t dimension){
    float coeff = vector1[0]/vector2[0];
    for(int8_t i =1;i<dimension; i++){
        if(coeff != vector1[i]/vector2[i]){
            return false;
        }
    }
    return true;
}
int main(){
    int8_t dimension = 3;
    float v1[3] = { 1, 2, 3};
    float v2[3] = { 2, 1,-1};

    printf("dot product: %f\n",dot_product(v1,v2,dimension));
    printf("vector 1 length: %f\n",vector_length(v1,dimension));
    printf("vector 2 length: %f\n",vector_length(v2,dimension));



    float *new_vector = vector_projection(v1,v2,dimension);
    if(new_vector == NULL){
        puts("Error!");
        exit(1);
    }

    print_vector(new_vector,dimension);
    free(new_vector);

    float *cross_product_result = cross_product(v1,v2,dimension);
    if(cross_product_result == NULL){
        puts("Error!");
        exit(1);
    }
    print_vector(cross_product_result,dimension);
    free(cross_product_result);

    float v3[3] = { 1, 2, 3};
    float v4[3] = { 2, 4, 6};

    if(check_for_parallel_vectors(v1,v2,dimension)){
        puts("They are parallel vectors");
    }
    else{
        puts("They are not parallel vectors");
    }

    if(check_for_parallel_vectors(v3,v4,dimension)){
        puts("They are parallel vectors");
    }
    else{
        puts("They are not parallel vectors");
    }



    return 0;
}

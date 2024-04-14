#include <stdio.h>

enum alimentos{
    arroz, feijao, macarrao, cenoura, batata, cebola, alho, olho
};


int main(){
    enum alimentos a = arroz;
    printf("%d\n", a);


    return 0;
}
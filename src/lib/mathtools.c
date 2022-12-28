#include "../include/mathtools.h"

int pn(int num, int power){
    int n = 1;
    for(int i = 1; i <= power; i++){
        n *= num;
    }
    return n;
}

int gcd(int num){
    int exp = 0;
    while(num >= 1){
        num = (double)num / 10;
        exp++;
    }
    return exp;
}

void numtostr(int n, char *str){
    char *chset = "0123456789";
    int mult = pn(10, gcd(n)-1);
    int i = 0;
    while(mult > 0){
        str[i] = chset[n/mult];
        i++;
        n = n - (n/mult) * mult;
        mult /= 10;
    }
    str[i] = '\0';
}
#include "stdio.h"

int main(){
    union {
        float f;
        unsigned char uc[sizeof(float)];
    } x;
    
    // Building +- Infinity : Exponent = 11111111 Fraction = 0
    
    x.uc[3] = 0b01111111;
    x.uc[2] = 0b10000000;
    x.uc[1] = 0b00000000;
    x.uc[0] = 0b00000000;
    printf("%.8e\n", x.f); // <- Would print inf

    x.uc[3] = 255;
    printf("%.8e\n", x.f); // <- Would print -inf


    // Building NaN : Exponent = 11111111 Fraction != 0
    x.uc[3] = 0b01111111;
    x.uc[2] = 0b10000000;
    x.uc[1] = 0b00000000;
    x.uc[0] = 0b00000001;
    printf("%.8e\n", x.f); // <- Would print nan
    x.uc[3] = 0b11111111;
    printf("%.8e\n", x.f); // <- Would print -nan
    


    // Important Note : In denormalized form, the exponent is 0, which may trick you to think that 
    // the biased exponent would be -127, but In fact, It is -126! 
    // Also in double, It is -1022 not -1023!
    
    // Building a denormalized number : Exponent = 0 , Fraction = 00000000000000000000001 (2^-23)
    // This number is the smalles denormalized number in float!
    x.uc[3] = 0b00000000;
    x.uc[2] = 0b00000000;
    x.uc[1] = 0b00000000;
    x.uc[0] = 0b00000001;
    printf("%.8e\n", x.f); // <- x = (-1)^0 * (0 + 2^ -23) * (2 ^ -126) = 2^(-149) = 1.40129846e-45

    // Another denormalized number :
    x.uc[3] = 0b10000000;
    x.uc[2] = 0b00000000;
    x.uc[1] = 0b00000000;
    x.uc[0] = 0b00000111;
    printf("%.8e\n", x.f); // <- x = (-1)^1 * (2^ -23 + 2^ -22 + 2^ -21) * (2 ^ -126) = -(2^ -149 + 2^ -148 + 2^ -147) = -9.80908925e-45


    // Building a regular floating point number
    x.uc[3] = 0b11000000; // Sign = 1 So its negative, exponent is 128 (biased), so it would be (128-127 = 1 unbiased) 
    x.uc[2] = 0b01000000; // the fraction is .1
    x.uc[1] = 0b00000000;
    x.uc[0] = 0b00000000; 
    printf("%.1e\n", x.f); // The number would be : -1 ^ 1 * (1.1)2 * 2^1 = -1 * 1.5 * 2 = -3.0e+00 or -3.0

    return 0;
}
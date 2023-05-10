#include <stdio.h>

int main(){
    float balance = 0.7f + 0.6f;
    printf("%f\n", balance);

    if(balance >= 1.3f){
        balance -= 1.3f;
        printf("Purchase Successful!");
    }
    else{
        printf("Insufficient Funds");
    }
}
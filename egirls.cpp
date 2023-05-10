#include "egirls.h"

void Egirls::increment(int daddyCount){
    count += daddyCount + 1;
}

void Egirls::perSecond(int catEarsCount){
    count += catEarsCount;
}

uint64_t Egirls::getCount() const{
    return count;
}

void Daddy::buy(Egirls& egirls){
    if(egirls.getCount() >= price){
        count++;
        egirls.count -= price;
        price += (count / 0.05);
    }
}
uint64_t Daddy::getCount() const{
    return count;
}

uint64_t Daddy::getPrice(){
    if(!first){
        uint64_t countincr = 1;
        for(uint64_t i=0;i<count;i++){
            price += (countincr / 0.05);
            countincr++;
        }
        first = 1;
    }
    return price;
}

void CatEars::buy(Egirls& egirls){
    if(egirls.getCount() >= price){
        count++;
        egirls.count -= price;
        price += (count / 0.01);
    }
}
uint64_t CatEars::getCount() const{
    return count;
}

uint64_t CatEars::getPrice(){
    if(!first){
        uint64_t countincr = 1;
        for(uint64_t i=0;i<count;i++){
            price += (countincr / 0.01);
            countincr++;
        }
        first = 1;
    }
    return price;
}
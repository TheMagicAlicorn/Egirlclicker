#include <cstdint>

#ifndef EGIRLS_H
#define EGIRLS_H

class Egirls{
public:
    void increment(int daddyCount);
    void perSecond(int catEarsCount);
    uint64_t getCount() const;
    uint64_t count;
private:

};

class Daddy{
public:
    void buy(Egirls& egirls);
    uint64_t getCount() const;
    uint64_t getPrice();
    uint64_t count;
private:
    uint64_t price = 50;
    int first = 0;
};

class CatEars{
public:
    void buy(Egirls& egirls);
    uint64_t getCount() const;
    uint64_t getPrice();
    uint64_t count;
private:
    uint64_t price = 1000;
    int first = 0;
};


#endif
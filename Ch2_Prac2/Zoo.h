#ifndef ZOO_H
#define ZOO_H

#include "Animal.h"

class Zoo
{
private:
    static constexpr int kMaxAnimalCount = 10;
    Animal* animals[kMaxAnimalCount];
    int _count = 0;
public:
    ~Zoo();

    void addAnimal(Animal* animal);
    void performActions();

    int count() const;
    int capacity() const;
    bool isFull() const;
};

#endif // ZOO_H
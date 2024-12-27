#include "Zoo.h"

#include <iostream>

Zoo::~Zoo()
{
    for (int i = 0; i < _count; i++) {
        delete animals[i];
    }
}

void Zoo::addAnimal(Animal* animal)
{
    if (isFull()) {
        return;
    }

    animals[_count++] = animal;
}

void Zoo::performActions()
{
    for (int i = 0; i < _count; i++) {
        animals[i]->makeSound();
        std::cout << std::endl;
    }
}

int Zoo::count() const
{
    return _count;
}

int Zoo::capacity() const
{
    return kMaxAnimalCount;
}

bool Zoo::isFull() const
{
    return _count >= kMaxAnimalCount;
}

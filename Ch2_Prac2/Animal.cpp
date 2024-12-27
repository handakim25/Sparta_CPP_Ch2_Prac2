#include "Animal.h"

#include <iostream>

void Cat::makeSound()
{
    std::cout << "Meow!";
}

std::string Cat::getName()
{
    return "Cat";
}

void Dog::makeSound()
{
    std::cout << "Woof!";
}

std::string Dog::getName()
{
    return "Dog";
}

void Cow::makeSound()
{
    std::cout << "Moo!";
}

std::string Cow::getName()
{
    return "Cow";
}

std::string Animal::getName()
{
    return "Animal";
}

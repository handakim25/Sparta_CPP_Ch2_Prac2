#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

class Animal
{
public:
    virtual void makeSound() = 0;
    virtual std::string getName();
};

class Cat : public Animal
{
public:
    void makeSound() override;
    virtual std::string getName() override;
};

class Dog : public Animal
{
public:
    void makeSound() override;
    virtual std::string getName() override;
};

class Cow : public Animal
{
public:
    void makeSound() override;
    virtual std::string getName() override;
};

#endif // ANIMAL_H

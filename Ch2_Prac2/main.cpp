#include <iostream>
#include <sstream>
#include <random>

#include "Animal.h"
#include "Zoo.h"

using namespace std;

Animal* CreateRandomAnimal();
Animal* CreateAnimalByIndex(int index);
int GenerateRandomNumber(int min, int max);

// command

const string commandList[] = { "Add Animal", "Add Random Animal", "Listen Sound", "Quit" };
const string divider = "-----";

int GetCommandInput(const string* commands, int commandCount);
int GetIntInput(const string& promptMessage, const string& errorMessage);
int GetIntInput(const string& promptMessage, const string& errorMessage, int min, int max);

// Handle Command

void AddAnimal(Zoo& zoo);
void AddRandomAnimal(Zoo& zoo);
void ListenSound(Zoo& zoo);
void HandleDefault(int command);

int main() {
    Zoo zoo;

    // �⺻ ���� ����
    for (int i = 0; i < 3; i++) {
        zoo.addAnimal(CreateAnimalByIndex(i));
    }
    zoo.performActions();

    int commandCount = sizeof(commandList) / sizeof(commandList[0]);
    int exitCommandIndex = 3;
    int command = -1;

    while ((command = GetCommandInput(commandList, commandCount)) != exitCommandIndex
        && command != -1)
    {
        switch (command)
        {
        case 0:
            AddAnimal(zoo);
            break;
        case 1:
            AddRandomAnimal(zoo);
            break;
        case 2:
            ListenSound(zoo);
            break;
        default:
            HandleDefault(command);
            break;
        }
    }

    return 0;
}


/// @brief ������ Animal�� ��ȯ�Ѵ�.(Cat, Cow, Dog)
/// @return ������ Animal ������
Animal* CreateRandomAnimal()
{
    int randomNumber = GenerateRandomNumber(0, 2);
    return CreateAnimalByIndex(randomNumber);
}

Animal* CreateAnimalByIndex(int index)
{
    switch (index)
    {
    case 0:
        return new Cat();
    case 1:
        return new Dog();
    case 2:
        return new Cow();
    default:
        return nullptr;
    }
}

/// @brief [min, max] ������ ������ ������ ��ȯ�Ѵ�.
/// @param min �ּڰ�
/// @param max �ִ�(include)
/// @return [min, max]�� ���� ����
int GenerateRandomNumber(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd()); // �Լ� ������ static ���� ������
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// command�� ����ϰ� ����ڷκ��� �Է��� �޾� command�� �ε����� ��ȯ�Ѵ�.
// commands : Ŀ�ǵ� ����Ʈ
// commandCount : Ŀ�ǵ� ����Ʈ�� ������
// return : ����ڷκ��� �Է� ���� command�� �ε���
int GetCommandInput(const string* commands, int commandCount)
{
    if (commandCount <= 0) {
        return -1;
    }

    ostringstream oss;

    oss << "Ŀ�ǵ� : ";
    for (int i = 0; i < commandCount; i++) {
        oss << commands[i] << ":" << i;
        if (i < commandCount - 1) {
            oss << ", ";
        }
    }
    oss << endl;
    oss << "Ŀ�ǵ带 ���ڷ� �Է����ּ���.(0-" << commandCount - 1 << "): ";

    return GetIntInput(oss.str(), "��ȿ�� �Է��� ���ּ���.", 0, commandCount - 1);
}

// ����ڷκ��� ���� �Է��� �޴´�.
// promptMessage : ����ڿ��� �Է��� �ޱ� ���� ����� �ؽ�Ʈ
// errorMessage : �߸��� �Է��� �޾��� ��� ����� �ؽ�Ʈ. empty�� ��� ������� �ʴ´�.
// return : ����ڷκ��� �Է� ���� ����
int GetIntInput(const string& promptMessage, const string& errorMessage)
{
    return GetIntInput(promptMessage, errorMessage, numeric_limits<int>::min(), numeric_limits<int>::max());
}

// ����ڷκ��� ���� �Է��� �޴´�.
// promptMessage : ����ڿ��� �Է��� �ޱ� ���� ����� �ؽ�Ʈ
// errorMessage : �߸��� �Է��� �޾��� ��� ����� �ؽ�Ʈ. empty�� ��� ������� �ʴ´�.
// min, max : �Է� ���� ���� ���� : [min, max]
// return : ����ڷκ��� �Է� ���� ����
int GetIntInput(const string& promptMessage, const string& errorMessage, int min, int max)
{
    int userInput = numeric_limits<int>::max();
    bool isFirst = true;

    // do-while�� �� ��� �ݵ�� �� �� ȣ���� �Ǿ continue�� ����� �������� �ʱ⿡ while ���� ������ ����ϵ��� �ߴ�.
    while (true) {
        if (!isFirst && !errorMessage.empty()) {
            cout << errorMessage << endl;
        }
        cout << promptMessage;
        cin >> userInput;

        // �Է� ��ȿ�� �˻�
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (userInput >= min && userInput <= max) {
            break;
        }

        isFirst = false;
    }

    return userInput;
}

/// @brief ����� �Է��� �޾Ƽ� ������ ������ �߰��Ѵ�.
/// @param zoo ����� zoo
void AddAnimal(Zoo& zoo)
{
    if (zoo.isFull()) {
        cout << "�������� ���� á���ϴ�." << endl;
        return;
    }

    cout << "�߰��� ������ �Է����ּ���." << endl
        << "Cat : 0, Dog : 1, Cow : 2" << endl;
    int animalIndex = GetIntInput("�ε��� : ", "��ȿ�� �Է��� ���ּ���.", 0, 2);

    zoo.addAnimal(CreateAnimalByIndex(animalIndex));

    cout << divider;
}

/// @brief ������ ������ �߰��Ѵ�.
/// @param zoo ����� zoo
void AddRandomAnimal(Zoo& zoo)
{
    if (zoo.isFull()) {
        cout << "�������� ���� á���ϴ�." << endl;
        return;
    }

    Animal* animal = CreateRandomAnimal();
    if (animal == nullptr) {
        cout << "���� �߻� : ���� ������ �����߽��ϴ�." << endl;
        return;
    }

    zoo.addAnimal(animal);

    cout << animal->getName() << "�� �����Ǿ����ϴ�." << endl;
    cout << divider;
}

/// @brief zoo �������� �Ҹ��� ��´�.
/// @param zoo ����� zoo
void ListenSound(Zoo& zoo)
{
    zoo.performActions();
    cout << divider;
}

/// @brief �߸��� �Է��� ó���Ѵ�.
/// @param command �߸��� command�� �ε���
void HandleDefault(int command)
{
    cout << "�߸��� �Է��Դϴ�. Comamnd : " << command << endl;
}
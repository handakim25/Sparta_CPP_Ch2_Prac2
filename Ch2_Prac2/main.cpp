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

    // 기본 동물 생성
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


/// @brief 랜덤한 Animal을 반환한다.(Cat, Cow, Dog)
/// @return 랜덤한 Animal 포인터
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

/// @brief [min, max] 범위의 랜덤한 정수를 반환한다.
/// @param min 최솟값
/// @param max 최댓값(include)
/// @return [min, max]의 랜덤 정수
int GenerateRandomNumber(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd()); // 함수 내부의 static 난수 생성기
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// command를 출력하고 사용자로부터 입력을 받아 command의 인덱스를 반환한다.
// commands : 커맨드 리스트
// commandCount : 커맨드 리스트의 사이즈
// return : 사용자로부터 입력 받은 command의 인덱스
int GetCommandInput(const string* commands, int commandCount)
{
    if (commandCount <= 0) {
        return -1;
    }

    ostringstream oss;

    oss << "커맨드 : ";
    for (int i = 0; i < commandCount; i++) {
        oss << commands[i] << ":" << i;
        if (i < commandCount - 1) {
            oss << ", ";
        }
    }
    oss << endl;
    oss << "커맨드를 숫자로 입력해주세요.(0-" << commandCount - 1 << "): ";

    return GetIntInput(oss.str(), "유효한 입력을 해주세요.", 0, commandCount - 1);
}

// 사용자로부터 정수 입력을 받는다.
// promptMessage : 사용자에게 입력을 받기 전에 출력할 텍스트
// errorMessage : 잘못된 입력을 받았을 경우 출력할 텍스트. empty일 경우 출력하지 않는다.
// return : 사용자로부터 입력 받은 정수
int GetIntInput(const string& promptMessage, const string& errorMessage)
{
    return GetIntInput(promptMessage, errorMessage, numeric_limits<int>::min(), numeric_limits<int>::max());
}

// 사용자로부터 정수 입력을 받는다.
// promptMessage : 사용자에게 입력을 받기 전에 출력할 텍스트
// errorMessage : 잘못된 입력을 받았을 경우 출력할 텍스트. empty일 경우 출력하지 않는다.
// min, max : 입력 받을 정수 범위 : [min, max]
// return : 사용자로부터 입력 받은 정수
int GetIntInput(const string& promptMessage, const string& errorMessage, int min, int max)
{
    int userInput = numeric_limits<int>::max();
    bool isFirst = true;

    // do-while을 할 경우 반드시 한 번 호출이 되어서 continue가 제대로 동작하지 않기에 while 무한 루프를 사용하도록 했다.
    while (true) {
        if (!isFirst && !errorMessage.empty()) {
            cout << errorMessage << endl;
        }
        cout << promptMessage;
        cin >> userInput;

        // 입력 유효성 검사
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

/// @brief 사용자 입력을 받아서 임의의 동물을 추가한다.
/// @param zoo 사용할 zoo
void AddAnimal(Zoo& zoo)
{
    if (zoo.isFull()) {
        cout << "동물원이 가득 찼습니다." << endl;
        return;
    }

    cout << "추가할 동물을 입력해주세요." << endl
        << "Cat : 0, Dog : 1, Cow : 2" << endl;
    int animalIndex = GetIntInput("인덱스 : ", "유효한 입력을 해주세요.", 0, 2);

    zoo.addAnimal(CreateAnimalByIndex(animalIndex));

    cout << divider;
}

/// @brief 랜덤한 동물을 추가한다.
/// @param zoo 사용할 zoo
void AddRandomAnimal(Zoo& zoo)
{
    if (zoo.isFull()) {
        cout << "동물원이 가득 찼습니다." << endl;
        return;
    }

    Animal* animal = CreateRandomAnimal();
    if (animal == nullptr) {
        cout << "에러 발생 : 동물 생성에 실패했습니다." << endl;
        return;
    }

    zoo.addAnimal(animal);

    cout << animal->getName() << "가 생성되었습니다." << endl;
    cout << divider;
}

/// @brief zoo 동물들의 소리를 듣는다.
/// @param zoo 사용할 zoo
void ListenSound(Zoo& zoo)
{
    zoo.performActions();
    cout << divider;
}

/// @brief 잘못된 입력을 처리한다.
/// @param command 잘못된 command의 인덱스
void HandleDefault(int command)
{
    cout << "잘못된 입력입니다. Comamnd : " << command << endl;
}
#include <iostream>

#include "Casino.h"
#include "User.h"
#include "Maquina.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese_Portugal.1252");

    Casino("Casino POO").Menu();
    return 0;
}

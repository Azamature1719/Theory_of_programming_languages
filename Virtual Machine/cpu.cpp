#include "cpu.h"     //! \include Описание процессора
#include "command.h" //! \include Объявление абстрактного класса процессора
#include "io.h"      //! \include Команды ввода-вывода
#include "arithmeticsfloat.h"    //! \include Команды дробной арифметики
#include "arithmeticsInteger.h"  //! \include Команды целочисленной арифметики
#include "arithmeticsAddress.h"  //! \include Команды адресной арифметики
#include "arithmeticsAddressNum.h" //! \include Команды адресной арифметики со смещением
#include "jump.h"      //! \include Команды переходов
#include "movements.h" //! \include Команды пересылок

using namespace std;

enum opcode
{
    /** Команда остановки */
    stop = 0,

    /** Команды ввода-вывода */
    //! Ввод-вывод целого числа (ввод: r1-0, вывод: r1-1)
    ioInt = 1,
    //! Ввод-вывод вещественного числа (ввод: r1-0, вывод: r1-1)
    ioFloat = 2,
    //! Ввод-вывод вещественного числа из регистра
    ioFromReg = 3,

    /** Команды загрузки и сохранения адресного регистра */
    loadReg = 4, //! Загрузка адресного регистра
    saveReg = 5, //! Сохранение адресного регистра в память
    exchAddReg = 6, //! Обмен значениями адресных регистров (r1-1), копирование адресных регистров (r1-0)
    fromMemToReg = 7, //! Пересылка память-регистр

    /** Команды целочисленной арифметики */
    intAdd = 8, //! Сложение
    intSub = 9, //! Вычитание
    intMult = 10, //! Умножение
    intDiv = 11, //! Деление

    /** Команды дробной арифметики */
    floatAdd = 12, //! Сложение
    floatSub = 13, //! Вычитание
    floatMult = 14, //! Умножение
    floatDiv = 15, //! Деление

    /** Команды адресной арифметики */
    addSh = 16, //! Сложение адресов
    subSh = 17, //! Вычитание адресов
    addShNum = 18, //! Сложение адреса и смещения
    subShNum = 19, //! Вычитания адреса и смещения

    /** Команды перехода */
    toSubpr = 20, //! Переход к подпрограмме
    fromSubpr = 21, //! Возврат из подпрограммы

    /** Команда безусловного перехода */
    uncondJump = 22,

    /** Команды условного перехода*/
    zfJump = 23, //! Переход с проверка флага нуля
    sfJump = 24, //! Переход с проверка знакового флага
    NOTzfJump = 25, //! Переход с проверкой инвертированного флага нуля
    NOTsfJump = 26, //! Переход с проверкой инвертированного флага знака
};

CPU::CPU()
{   
    /** Остановка выполнения программы */
    commandCPU[stop] = nullptr;

    /** Команды ввода-вывода */
    commandCPU[ioInt] = new class ioInt();  //! Ввод-вывод целого числа
    commandCPU[ioFloat] = new class ioFl(); //! Ввод-вывод вещественного числа
    commandCPU[ioFromReg] = new class ioReg(); //! Ввод-вывод числа из регистра

    /** Команды загрузки адресного регистра */
    commandCPU[loadReg] = new class uploadAddReg(); //! Сохранение адреса из команды в регистр
    commandCPU[saveReg] = new class saveAddReg();   //! Сохранение адреса из адресного регистра в память
    commandCPU[exchAddReg] = new class exchAddReg();//! Обмен/копирование адресов адресных регистров
    commandCPU[fromMemToReg] = new class fromMemoryToReg(); //! Пересылка из памяти в регистр

    /** Команды арифметики */
    /** Целочисленная арифметики */
    commandCPU[intAdd] = new class addIntLong();    //! Сложение
    commandCPU[intSub] = new class subIntLong();    //! Вычитание
    commandCPU[intMult] = new class multIntLong();  //! Умножение
    commandCPU[intDiv] = new class divIntLong();    //! Деление

    /** Дробная арифметики */
    commandCPU[floatAdd] = new class addFlLong();   //! Сложение
    commandCPU[floatSub] = new class subFlLong();   //! Вычитание
    commandCPU[floatMult] = new class multFlLong(); //! Умножение
    commandCPU[floatDiv] = new class divFlLong();   //! Деление

    /** Команды адресной арифметики */
    commandCPU[addSh] = new class addShort();       //! Сложение
    commandCPU[subSh] = new class subShort();       //! Вычитание
    commandCPU[addShNum] = new class addShortNum(); //! Сложение адреса и смещения
    commandCPU[subShNum] = new class subShortNum(); //! Вычитание адреса и смещения

    /** Команды переходов */
    commandCPU[uncondJump] = new class Uncoditional(); //! Безусловный переход
    commandCPU[zfJump] = new class ConditionalZF();    //! Переход с проверкой флага нуля
    commandCPU[NOTzfJump] = new class ConditionalNOTzf(); //! Переход с проверкой инвертированного флага нуля
    commandCPU[NOTsfJump] = new class ConditionalNOTsf(); //! Переход с проверкой инвертированного знакового флага
    commandCPU[sfJump] = new class ConditionalSF();    //! Переход с проверкой флага знака
    commandCPU[toSubpr] = new class ToProgram();       //! Вызов подпрограммы
    commandCPU[fromSubpr] = new class Return();        //! Возврат из подпрограммы
}

//! \brief CPU::execute - функция запуска процессора
void CPU::execute() noexcept
{
    //! \brief uploadCommand - загрузка команды процессора
    command = memory.pop_memory(PSW.IP).anyCommand;
    //! Выполнение производится пока не считана команда остановки
    while(command.cmdU.opcode != stop)
    {
        commandCPU[command.cmdU.opcode]->operator()(*this);
        //! Переход на следующую команду
        ++PSW.IP;
        //! \brief Если совершается переход, в функции перехода адрес уменьшается на единицу
        command = memory.pop_memory(PSW.IP).anyCommand;
    }
}

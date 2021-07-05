#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <cinttypes>

//! \brief address - адрес памяти
using address = uint16_t;

//! \brief addressReg - номер адресного регистра
using addressReg = uint8_t;

//! \brief MemoryData - значение из памяти
using MemoryData = uint32_t;

//! \struct The UsualCommandStruct struct - структура команды процессора
struct UsualCommandStruct
{
    uint8_t opcode;    //! Код операции
    addressReg r1;     //! Первый номер регистра (хранит адрес результата выполненной операции)
    addressReg r2;     //! Второй номер регистра
    addressReg r3;     //! Третий номер регистра
};

//! \struct The AddressCommandStruct struct - структура команды загрузки адресного регистра
struct AddressCommandStruct
{
    uint8_t opcode;  //! Код операции
    uint8_t r1;      //! Номер загружаемого регистра
    address address; //! Адрес, который будет загружен в регистр
};

//! \union The CommandType - типы доступных команд
union CommandType
{
    UsualCommandStruct cmdU;    //! Обычная команда
    AddressCommandStruct cmdAR; //! Команда загрузки адресного регистра
};

//! \union The DataType union - используемые типы данных
union DataType
{
    uint32_t uintEl;    //! Целое беззнаковое число
    int32_t intEl;      //! Целое знаковое число
    float flEl;         //! Знаковое дробное число
    CommandType anyCommand; //! Команда любого вида
    address address; //! Адрес 16 бит
};

#endif // STRUCTURES_H

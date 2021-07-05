#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "windows.h"
#include "cpu.h"

using namespace std;

/**
 * @brief Uploader - загрузчик программы для виртуальной машины
 * @param processor - экземпляр процессора
 * @param filename - название загрузочного файла
 * @return - возвращает истину, если файл считался, ложь - если не считался
 */
bool Uploader(CPU &processor, const string &filename)
{
    //! \brief file - открытие файла с программой
    //! \return - возвращается ложь - если файл не открылся
    ifstream file(filename);
    if(!file.is_open())
        return false;

    //! \brief currAddress - текущий адрес,
    //! \brief startAddress - адрес загрузки
    address currAddress = 0, startAddress = 0;

    //! \brief type - тип операции
    char type = ' ';

    //! Пока не считана команда остановки, продолжить чтение
    while(type != 's') //! 's' - команда остановки считывания
    {
        string line;
        getline(file, line); //! Считывание всей команды

        istringstream readElem(line);
        readElem >> type; //! Считывание типа команды

        switch(type)
        {
        case 'a': //! Установка базового адреса загрузки
        {
            readElem >> startAddress;
            currAddress = startAddress;
        }
        break;

        case 'i': //! Загрузка целого знакового числа
        {
            //! \brief num - буфер для считывания числа
            DataType num;
            readElem >> num.intEl;
            processor.memory.push_memory(num, currAddress);
            ++currAddress;
        }
        break;

        case 'u': //! Загрузка целого беззнакового числа
        {
            //! \brief num - буфер для считывания числа
            DataType num;
            readElem >> num.uintEl;
            processor.memory.push_memory(num, currAddress);
            ++currAddress;
        }
        break;

        case 'f': //! Загрузка дробного числа
        {
            //! \brief num - буфер для считывания числа
            DataType num;
            readElem >> num.flEl;
            processor.memory.push_memory(num, currAddress);
            ++currAddress;
        }
        break;

        case 'r': //! Команда загрузки адресного регистра
        {
            //! \brief cmd - загружаемая команда
            DataType cmd;
            //! \brief - буфер для считывания элементов команды
            uint16_t bufLoad;
            readElem >> bufLoad;
            cmd.anyCommand.cmdAR.opcode = uint8_t(bufLoad);
            readElem >> bufLoad;
            cmd.anyCommand.cmdAR.r1 = uint8_t(bufLoad);
            readElem >> bufLoad;
            cmd.anyCommand.cmdAR.address = bufLoad;
            processor.memory.push_memory(cmd, currAddress);
            ++currAddress;
        }
        break;

        case 'c': //! Загрузка команды процессора
        {
            //! \brief cmd - загружаемая команда
            DataType cmd;
            //! \brief - буфер для считывания элементов команды
            uint16_t bufLoad;
            readElem >> bufLoad;
            cmd.anyCommand.cmdU.opcode = uint8_t(bufLoad);
            readElem >> bufLoad;
            cmd.anyCommand.cmdU.r1 = uint8_t(bufLoad);
            readElem >> bufLoad;
            cmd.anyCommand.cmdU.r2 = uint8_t(bufLoad);
            readElem >> bufLoad;
            cmd.anyCommand.cmdU.r3 = uint8_t(bufLoad);
            processor.memory.push_memory(cmd, currAddress);
            ++currAddress;
        }
        break;

        case 's': //! Остановка считывания, программный код загружен
        {
            //! \brief cmd - команда остановки считывания
            DataType cmd;
            //! КОП команды стоп - 0
            cmd.anyCommand.cmdU.opcode = 0;
            processor.memory.push_memory(cmd, currAddress);

            //! \brief IP - адрес первой для выполнения команды процессора
            address IP;
            readElem >> IP;
            processor.PSW.IP = IP;
        }
        break;
        }
    }
    system("pause");
    file.close();

    //! Возвращается истина при удачной загрузки программы
    return true;
}

int main(int argc, char* argv[])
{
    system("chcp 1251 > nul");

    CPU processor;

    if(argc>1) //! Если получено название файла
    {
        if(Uploader(processor, argv[1]))
        cout << "\nФайл успешно загружен!" << endl << endl << argv[1];
        else cout << "\nФайл не может быть загружен";
        processor.execute();
    }
    else cout << "\nФайл не найден!";
    cout << endl << endl;
    system("pause");
    return 0;
}

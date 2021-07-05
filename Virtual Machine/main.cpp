#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "windows.h"
#include "cpu.h"

using namespace std;

/**
 * @brief Uploader - ��������� ��������� ��� ����������� ������
 * @param processor - ��������� ����������
 * @param filename - �������� ������������ �����
 * @return - ���������� ������, ���� ���� ��������, ���� - ���� �� ��������
 */
bool Uploader(CPU &processor, const string &filename)
{
    //! \brief file - �������� ����� � ����������
    //! \return - ������������ ���� - ���� ���� �� ��������
    ifstream file(filename);
    if(!file.is_open())
        return false;

    //! \brief currAddress - ������� �����,
    //! \brief startAddress - ����� ��������
    address currAddress = 0, startAddress = 0;

    //! \brief type - ��� ��������
    char type = ' ';

    //! ���� �� ������� ������� ���������, ���������� ������
    while(type != 's') //! 's' - ������� ��������� ����������
    {
        string line;
        getline(file, line); //! ���������� ���� �������

        istringstream readElem(line);
        readElem >> type; //! ���������� ���� �������

        switch(type)
        {
        case 'a': //! ��������� �������� ������ ��������
        {
            readElem >> startAddress;
            currAddress = startAddress;
        }
        break;

        case 'i': //! �������� ������ ��������� �����
        {
            //! \brief num - ����� ��� ���������� �����
            DataType num;
            readElem >> num.intEl;
            processor.memory.push_memory(num, currAddress);
            ++currAddress;
        }
        break;

        case 'u': //! �������� ������ ������������ �����
        {
            //! \brief num - ����� ��� ���������� �����
            DataType num;
            readElem >> num.uintEl;
            processor.memory.push_memory(num, currAddress);
            ++currAddress;
        }
        break;

        case 'f': //! �������� �������� �����
        {
            //! \brief num - ����� ��� ���������� �����
            DataType num;
            readElem >> num.flEl;
            processor.memory.push_memory(num, currAddress);
            ++currAddress;
        }
        break;

        case 'r': //! ������� �������� ��������� ��������
        {
            //! \brief cmd - ����������� �������
            DataType cmd;
            //! \brief - ����� ��� ���������� ��������� �������
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

        case 'c': //! �������� ������� ����������
        {
            //! \brief cmd - ����������� �������
            DataType cmd;
            //! \brief - ����� ��� ���������� ��������� �������
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

        case 's': //! ��������� ����������, ����������� ��� ��������
        {
            //! \brief cmd - ������� ��������� ����������
            DataType cmd;
            //! ��� ������� ���� - 0
            cmd.anyCommand.cmdU.opcode = 0;
            processor.memory.push_memory(cmd, currAddress);

            //! \brief IP - ����� ������ ��� ���������� ������� ����������
            address IP;
            readElem >> IP;
            processor.PSW.IP = IP;
        }
        break;
        }
    }
    system("pause");
    file.close();

    //! ������������ ������ ��� ������� �������� ���������
    return true;
}

int main(int argc, char* argv[])
{
    system("chcp 1251 > nul");

    CPU processor;

    if(argc>1) //! ���� �������� �������� �����
    {
        if(Uploader(processor, argv[1]))
        cout << "\n���� ������� ��������!" << endl << endl << argv[1];
        else cout << "\n���� �� ����� ���� ��������";
        processor.execute();
    }
    else cout << "\n���� �� ������!";
    cout << endl << endl;
    system("pause");
    return 0;
}

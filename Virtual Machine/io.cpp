#include "io.h"

/** *********************************************************************** */
/** --------------------------������� �����-������------------------------- */
/** *********************************************************************** */

/**
 * @brief ioInt::operator() - ������� �����/������ ����� �����,
 * �������� ���������������� ��������� ������� ��������: 0 - ����, 1 - �����.
 * @param processor - ���������. ������ � ����������, ����� ������ ���
 * �������� �������� � ������ � ������� �� ������ ����������.
 * @return - ������ �� ������������
 */

void ioInt::operator()(CPU &processor) noexcept
{
    //! \brief buf - ����� ����������
    DataType buf;
    if(!processor.get_cmd_r1())
    {
        std::cout << "\n���� int: ";
        std::cin >> buf.intEl;
        processor.memory.push_memory(buf, processor.get_cmdAR_address());
    }
    else
    {
        buf = processor.memory.pop_memory(processor.get_cmdAR_address());
        std::cout << "\n����� int: " << buf.intEl;
    }
}

/**
 * @brief ioFl::operator() - ������� �����-������ ������������ �����,
 * �������� ���������������� ��������� ������� ��������: 0 - ����, 1 - �����.
 * @param processor - ���������. ������ � ���������� ����� ������ ���
 * �������� �������� � ������ � ������� �� ������ ����������.
 * @return - ������ �� ������������
 */

void ioFl::operator()(CPU &processor) noexcept
{
    //! \brief buf - ����� ����������
    DataType buf;
    if(!processor.get_cmd_r1())
    {
        std::cout << "\n���� float: ";
        std::cin >> buf.flEl;
        processor.memory.push_memory(buf,processor.get_cmdAR_address());
    }
    else
    {
        buf = processor.memory.pop_memory(processor.get_cmdAR_address());
        std::cout << "\n����� float: " << buf.flEl;
    }
}

/**
 * @class The ioReg class - ����/����� ������/�������� ����� �� ��������
 * � r1: 0 - ����, 1 - ����� (���� �� ������ � �������� r3)
 * � r2: 0 - �����, 1 - �������
 * � r3: ����� ���������� ��������, �������� �����
 */

void ioReg::operator()(CPU &processor) noexcept
{                                                //! 0/1
    addressReg print = processor.get_cmd_r1(),   //! ����/�����
            floating = processor.get_cmdU_r2(),  //! �����/�������
            regNum = processor.get_cmdU_r3();    //! ����� ���������� ��������

    DataType buf; //! ���������� - �����

    if(!print)
    {
       if(!floating)
       {
           std::cout << "\n���� int: ";
           std::cin >> buf.intEl;
           processor.memory.push_memory(buf, processor.addressRegister[regNum]);
       }
       else
       {
           std::cout << "\n���� float: ";
           std::cin >> buf.flEl;
           processor.memory.push_memory(buf, processor.addressRegister[regNum]);
       }
    }
    else
    {
        if(!floating)
        {
            buf = processor.memory.pop_memory(processor.addressRegister[regNum]);
            std::cout << "\n����� int: " << buf.intEl;
        }
        else
        {
            buf = processor.memory.pop_memory(processor.addressRegister[regNum]);
            std::cout << "\n����� float: " << buf.flEl;
        }
    }
}

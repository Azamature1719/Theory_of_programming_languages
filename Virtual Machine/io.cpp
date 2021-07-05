#include "io.h"

/** *********************************************************************** */
/** --------------------------КОМАНДЫ ВВОДА-ВЫВОДА------------------------- */
/** *********************************************************************** */

/**
 * @brief ioInt::operator() - команда ввода/вывода целых чисел,
 * операция конкретизируется значением первого регистра: 0 - ввод, 1 - вывод.
 * @param processor - процессор. Доступ к процессору, нужен потому что
 * значения вносятся в память и берутся из памяти процессора.
 * @return - ничего не возвращается
 */

void ioInt::operator()(CPU &processor) noexcept
{
    //! \brief buf - буфер переменной
    DataType buf;
    if(!processor.get_cmd_r1())
    {
        std::cout << "\nВВОД int: ";
        std::cin >> buf.intEl;
        processor.memory.push_memory(buf, processor.get_cmdAR_address());
    }
    else
    {
        buf = processor.memory.pop_memory(processor.get_cmdAR_address());
        std::cout << "\nВЫВОД int: " << buf.intEl;
    }
}

/**
 * @brief ioFl::operator() - команда ввода-вывода вещественных чисел,
 * операция конкретизируется значением первого регистра: 0 - ввод, 1 - вывод.
 * @param processor - процессор. Доступ к процессору нужен потому что
 * значения вносятся в память и берутся из памяти процессора.
 * @return - ничего не возвращается
 */

void ioFl::operator()(CPU &processor) noexcept
{
    //! \brief buf - буфер переменной
    DataType buf;
    if(!processor.get_cmd_r1())
    {
        std::cout << "\nВВОД float: ";
        std::cin >> buf.flEl;
        processor.memory.push_memory(buf,processor.get_cmdAR_address());
    }
    else
    {
        buf = processor.memory.pop_memory(processor.get_cmdAR_address());
        std::cout << "\nВЫВОД float: " << buf.flEl;
    }
}

/**
 * @class The ioReg class - ввод/вывод целого/дробного числа из регистра
 * в r1: 0 - ввод, 1 - вывод (ввод по адресу в регистре r3)
 * в r2: 0 - целое, 1 - дробное
 * в r3: номер выводимого регистра, регистра ввода
 */

void ioReg::operator()(CPU &processor) noexcept
{                                                //! 0/1
    addressReg print = processor.get_cmd_r1(),   //! Ввод/вывод
            floating = processor.get_cmdU_r2(),  //! Целое/дробное
            regNum = processor.get_cmdU_r3();    //! Номер выводимого регистра

    DataType buf; //! Переменная - буфер

    if(!print)
    {
       if(!floating)
       {
           std::cout << "\nВВОД int: ";
           std::cin >> buf.intEl;
           processor.memory.push_memory(buf, processor.addressRegister[regNum]);
       }
       else
       {
           std::cout << "\nВВОД float: ";
           std::cin >> buf.flEl;
           processor.memory.push_memory(buf, processor.addressRegister[regNum]);
       }
    }
    else
    {
        if(!floating)
        {
            buf = processor.memory.pop_memory(processor.addressRegister[regNum]);
            std::cout << "\nВЫВОД int: " << buf.intEl;
        }
        else
        {
            buf = processor.memory.pop_memory(processor.addressRegister[regNum]);
            std::cout << "\nВЫВОД float: " << buf.flEl;
        }
    }
}

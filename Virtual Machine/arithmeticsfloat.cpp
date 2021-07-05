#include "arithmeticsFloat.h"

/** *********************************************************************** */
/** ----------------------КОМАНДЫ ДРОБНОЙ АРИФМЕТИКИ----------------------- */
/** *********************************************************************** */

/**
 * @brief arithmFlLong::setFlags - команда установки флагов.
 * @param processor - процессор, в классе процессора описаны флаги состояния,
 * которые могут быть изменены в данной функции.
 * @return - ничего не возвращается.
 */

void arithmFlLong::setFlags(CPU &processor) noexcept
{
    //! \brief address - адрес, лежащий в адресном регистре, номер которого указан в команде
    address address = processor.addressRegister[processor.get_cmd_r1()];

    //! \brief number - дробное число взятое из памяти по адресу
    float number = processor.memory.pop_memory(address).flEl;

    /** Сравнение числа с нулём и установка флагов */
    if(number == 0) {processor.PSW.ZF = 1;}
    else if (number < 0) {processor.PSW.SF = 1;}
}

/**
 * @brief arithmFlLong::operator () - вычислительная команда.
 * @param processor - процессор. Доступ к процессору нужен потому что
 * в функции возвращаются адреса из регистров и значения из памяти,
 * адресные регистры и память описаны в классе процессора.
 * @return - ничего не возвращается.
 */

void arithmFlLong::operator()(CPU &processor) noexcept
{
    //! \brief resultAddress - адрес, лежащий в адресном регистре, номер которого указан в команде
    address resultAddress = processor.addressRegister[processor.get_cmd_r1()];

    //! \brief paramAddress1 - адрес из первого регистра команды
    //! \brief paramAddress2 - адрес из второго регистра команды
    address paramAddress1 = processor.addressRegister[processor.get_cmdU_r2()],
            paramAddress2 = processor.addressRegister[processor.get_cmdU_r3()];

    //! \brief parametr1 - число из памяти, взятое по адресу из первого регистра
    //! \brief parametr2 - число из памяти, взятое по адресу из второго регистра
    int parametr1 = processor.memory.pop_memory(paramAddress1).intEl,
        parametr2 = processor.memory.pop_memory(paramAddress2).intEl;

    /** Выполнение вычисления */
    DataType result;
    result.flEl = calculation(parametr1, parametr2);
    processor.memory.push_memory(result, resultAddress);

    /** Установка флагов по результатам выполнения команды */
    setFlags(processor);
}


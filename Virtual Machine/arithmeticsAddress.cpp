#include "arithmeticsAddress.h"

/** *********************************************************************** */
/** --------------------КОМАНДЫ АДРЕСНОЙ АРИФМЕТИКИ------------------------ */
/** *********************************************************************** */

/**
 * @brief arithmShort::operator () - команда адресной арифметики (сложение/вычитание адресов)
 * @param processor - процессор. Доступ к процессору нужен потому что
 * в функции возвращаются адреса из регистров и значения из памяти,
 * адресные регистры и память описаны в классе процессора.
 * @return - ничего не возвращается
 */

void arithmShort::operator()(CPU &processor) noexcept
{
    //! \brief regResult - номер регистра, куда сохраняется результат вычисления нового адреса
    //! \brief regNum1 - первый регистр, откуда берётся адрес
    //! \brief regNum2 - второй регистр, откуда берётся адрес
    addressReg regResult = processor.get_cmd_r1(),
               regNum1 = processor.get_cmdU_r2(),
               regNum2 = processor.get_cmdU_r3();

    //! \brief parametr1 - адрес из первого регистра
    //! \brief parametr2 - адрес из второго регистра
    address parametr1 = processor.addressRegister[regNum1],
            parametr2 = processor.addressRegister[regNum2];

    //! \brief result - новый вычисленный адрес
    address result = calculation(parametr1, parametr2);
    processor.addressRegister[regResult] = result;
}

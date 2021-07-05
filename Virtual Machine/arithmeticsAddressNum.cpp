#include "arithmeticsAddressNum.h"

/** *********************************************************************** */
/** ------------------АДРЕСНАЯ АРИФМЕТИКА СО СМЕЩЕНИЕМ--------------------- */
/** *********************************************************************** */

void arithmShortNum::operator()(CPU &processor) noexcept
{
    //! \brief regNum - номер адресного регистра в команде
    addressReg regNum = processor.get_cmd_r1();

    //! \brief resultAddress - базовый адрес из первого регистра команды
    address resultAddress = processor.addressRegister[regNum];

    //! \brief replace - смещение из константного поля команды
    address replace = processor.get_cmdAR_address();

    //! \brief replacedAddress - вычисление нового адреса
    address replacedAddress = calculation(resultAddress, replace);
    processor.addressRegister[regNum] = replacedAddress;
}

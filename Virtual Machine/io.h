#ifndef IO_H
#define IO_H

#include "command.h"

/** *********************************************************************** */
/** --------------------------КОМАНДЫ ВВОДА-ВЫВОДА------------------------- */
/** *********************************************************************** */

/**
 * @class The ioInt class - ввод/вывод целого числа по адресу,
 * команда конкретизируется в первом регистре r1
 */

class ioInt : public Command
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/**
 * @class The ioFl class - ввод/вывод дробного числа,
 * команда конкретизируется в первом регистре r1
 */

class ioFl : public Command
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/**
 * @class The ioReg class - ввод/вывод целого/дробного числа из регистра
 * в r1: 0 - ввод, 1 - вывод
 * в r2: 0 - целое, 1 - дробное
 * в r3: номер выводимого регистра
 */
class ioReg : public Command
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

#endif // IO_H

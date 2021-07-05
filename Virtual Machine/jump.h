#ifndef JUMP_H
#define JUMP_H

#include "command.h"

/** *********************************************************************** */
/** --------------------------КОМАНДЫ ПЕРЕХОДОВ---------------------------- */
/** *********************************************************************** */

/**
 * @class The Jump class - класс команд переходов
 */

class Jump : public Command
{
    //! \brief jumpTo - команда условного перехода
    //! \param processor - экземпляр класса процессора
    //! \return - возвращается истина, если по результатам проверки
    //! флагов необходимо совершить переход, ложь - в противном случае
    virtual bool jumpTo (CPU &processor) noexcept = 0;

public:
    virtual void operator()(CPU &processor) noexcept override final;
    void forwardJ(CPU &processor);
    void forwardIndJ(CPU &processor);
    void forwardIndRegJ (CPU &processor);
    void relativeJ(CPU &processor);
};

/**
 * @class The Uncoditional class - команда безусловного перехода (без проверки флагов)
 */

class Uncoditional : public Jump
{
    virtual bool jumpTo(CPU &processor) noexcept override;
};

/**
 * @class The ConditionalZF class - условный переход с проверкой флага нуля
 */

class ConditionalZF : public Jump
{
    virtual bool jumpTo(CPU &processor) noexcept override;
};

class ConditionalNOTzf : public Jump
{
    virtual bool jumpTo(CPU &processor) noexcept override;
};

/**
 * @class The ConditionalSF class - условный переход с проверкой знакового флага
 */

class ConditionalSF : public Jump
{
    virtual bool jumpTo(CPU &processor) noexcept override;
};


class ConditionalNOTsf : public Jump
{
    virtual bool jumpTo(CPU &processor) noexcept override;
};

/**
 * @class The ToProgram class - переход к подпрограмме,
 * всегда возвращает ложь, IP меняется внутри функции
 */

class ToProgram : public Jump
{
    virtual bool jumpTo(CPU &processor) noexcept override;
};

/**
 * @class The Return class - возврат из подпрограммы,
 * всегда возвращает ложь, IP меняется внутри функции
 */

class Return : public Jump
{
    virtual bool jumpTo(CPU &processor) noexcept override;
};

#endif // JUMP_H

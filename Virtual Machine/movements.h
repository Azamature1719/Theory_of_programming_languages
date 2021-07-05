#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "command.h"

/** *********************************************************************** */
/** ---------------------------КОМАНДА ПЕРЕСЫЛКИ--------------------------- */
/** *********************************************************************** */

/**
 * @class The uploadAddReg class - команда загрузки адресного регистра
 */

class uploadAddReg : public Command
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/**
 * @class The saveAddReg class - команда сохранения адресного регистра в память (регистр-память)
 */

class saveAddReg : public Command
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/**
 * @class The fromMemoryToReg class - команда пересылки память-регистр
 */
class fromMemoryToReg : public Command
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/**
 * @class The exchAddReg class - копирование/обмен адресных регистров
 */

class exchAddReg : public Command
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

#endif // MOVEMENTS_H

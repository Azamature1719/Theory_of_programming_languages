#ifndef ARITHMETICSADDRESSNUM_H
#define ARITHMETICSADDRESSNUM_H

#include "command.h"

/** *********************************************************************** */
/** ------------------АДРЕСНАЯ АРИФМЕТИКА СО СМЕЩЕНИЕМ--------------------- */
/** *********************************************************************** */

/**
 * @class The arithmShortNum class - сложение/вычитание адреса в регистре и смещения в команде
 */

class arithmShortNum : public Command
{
    /**
     * @brief calculation - вычислительная команда над адресом и смещением
     * @param addressBase - базовый адрес в регистре
     * @param replace - смещение
     * @return возвращает смещённый адрес в регистре
     */
    virtual address calculation(address addressBase, address replace) noexcept = 0;
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/**
 * @class The addShortNum class - команда сложение адреса и целого смещения
 */

class addShortNum : public arithmShortNum
{
    /**
     * @brief calculation - сложение адреса и смещения
     * @param addressBase - базовый адрес в регистре
     * @param replace - целое смещение
     * @return возваращает сумму адреса и смещения
     */
    virtual address calculation(address addressBase, address replace) noexcept override final
    { return addressBase + replace;}
};

/**
 * @class The subShortNum class - вычитание адреса и целого смещения
 */

class subShortNum : public arithmShortNum
{
    /**
     * @brief calculation - вычитание двух смещения из адреса
     * @param addressBase - базовый адрес в регистре
     * @param replace - целое смещение
     * @return возвращает разность адреса и смещения
     */
    virtual address calculation(address addressBase, address replace) noexcept override final
    { return addressBase - replace;}
};
#endif // ARITHMETICSADDRESSNUM_H

#ifndef ARITHMETICSADDRESS_H
#define ARITHMETICSADDRESS_H

#include "command.h"

/** *********************************************************************** */
/** --------------------------АДРЕСНАЯ АРИФМЕТИКА-------------------------- */
/** *********************************************************************** */

/** Команды адресной арифметики. Только в адресных регистрах. Используется
 *  формат команды загрузки адресного регистра, в r1 - номер регистра, в поле
 *  адреса - адрес*/

/**
 * @class The arithmShort class - сложение/вычитание адресов из регистров
 */

class arithmShort : public Command
{
    /**
     * @brief calculation - вычислительная команда над адресами
     * @param address1 - адрес в первом регистре
     * @param address2 - адрес во втором регистре
     * @return возвращается результат действий над адресами
     */
    virtual address calculation(address address1, address address2) noexcept = 0;
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/**
 * @class The addShort class - команда сложения адресов
 */

class addShort : public arithmShort
{
    /**
     * @brief calculation - сложение двух беззнаковых чисел (адресов)
     * @param address1 - адрес в первом регистре
     * @param address2 - адрес во втором регистре
     * @return возвращается сумма адресов
     */
    virtual address calculation(address address1, address address2) noexcept override final
    { return address1 + address2;}
};

/**
 * @class The subShort class - команда вычитания адресов
 */

class subShort: public arithmShort
{
    /**
     * @brief calculation - разность двух беззнаковых чисел (адресов)
     * @param address1 - адрес в первом регистре
     * @param address2 - адрес во втором регистре
     * @return возвращается разность адресов
     */
    virtual address calculation(address address1, address address2) noexcept override final
    { return address1 - address2;}
};

#endif // ARITHMETICSADDRESS_H

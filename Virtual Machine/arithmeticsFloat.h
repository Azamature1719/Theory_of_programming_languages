#ifndef ARITHMETICSFLOAT_H
#define ARITHMETICSFLOAT_H

#include "command.h"

/** *********************************************************************** */
/** --------------------------КОМАНДЫ АРИФМЕТИКИ--------------------------- */
/** *********************************************************************** */

/** Команды длинной арифметики ([r1] = [r2] $ [r3]). Только в памяти.
 *  Адреса в адресных регистрах. В функцию передаются значения (числа) из памяти.
 *  Результат действий записывается в память по адресу, лежащему в первом регистре команды.
*/

/** *********************************************************************** */
/** -----------------------КОМАНДЫ ДРОБНОЙ АРИФМЕТИКИ---------------------- */
/** *********************************************************************** */

/**
 * @class The arithmFlLong class - команды дробной арифметики
 */

class arithmFlLong : public Command
{
    /**
     * @brief setFlags - команда установки флагов по результатам вычислений
     * @param processor - процессор необходим для доступа к регистру PSW
     */
    void setFlags(CPU &processor) noexcept;

    /**
     * @brief calculation - вычислительная команда
     * @param parametr1, @param parametr2 - значения, над которыми проводятся вычисления
     * @return возвращается результат операции
     */
    virtual float calculation(float parametr1, float parametr2) noexcept = 0;

public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/**
 * @class The addFlLong class - команда сложения дробных чисел
 */

class addFlLong : public arithmFlLong
{
    /**
     * @brief calculation - команда сложения
     * @param parametr1 - первое слагаемое
     * @param parametr2 - второе слагаемое
     * @return возвращается сумма двух слагаемых
     */
    virtual float calculation(float parametr1, float parametr2) noexcept override final
    { return parametr1 + parametr2; }
};

/**
 * @class The subFlLong class - команда вычитания дробных чисел
 */

class subFlLong: public arithmFlLong
{
    /**
     * @brief calculation - вычислительная команда
     * @param parametr1 - уменьшаемое
     * @param parametr2 - вычитаемое
     * @return возвращается разность двух чисел
     */
    virtual float calculation(float parametr1, float parametr2) noexcept override final
    { return parametr1 - parametr2; }
};

/**
 * @class The multFlLong class - команда умножения дробных чисел
 */

class multFlLong : public arithmFlLong
{
    /**
     * @brief calculation - вычислительная команда
     * @param parametr1 - первый множитель
     * @param parametr2 - второй множитель
     * @return возвращается произведение множителей
     */
    virtual float calculation(float parametr1, float parametr2) noexcept override final
    { return parametr1 * parametr2; }
};

/**
 * @class The divFlLong class - команда деления дробных чисел
 */

class divFlLong : public arithmFlLong
{
    /**
     * @brief calculation - вычислительная команда
     * @param parametr1 - делимое
     * @param parametr2 - делитель
     * @return возвращается частное от деления
     */
    virtual float calculation(float parametr1, float parametr2) noexcept override final
    { return parametr1 / parametr2; }
};

#endif // ARITHMETICSFLOAT_H

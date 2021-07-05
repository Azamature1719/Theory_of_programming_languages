#ifndef ARITMETICSNUMBERS_H
#define ARITMETICSNUMBERS_H

#include "command.h"

/** *********************************************************************** */
/** --------------------------КОМАНДЫ АРИФМЕТИКИ--------------------------- */
/** *********************************************************************** */

/** Команды длинной арифметики ([r1] = [r2] $ [r3]). Только в памяти.
 *  Адреса в адресных регистрах. В функцию передаются значения (числа) из памяти.
 *  Результат действий записывается в память по адресу, лежащему в первом регистре.
*/

/** *********************************************************************** */
/** -----------------------ЦЕЛОЧИСЛЕННАЯ АРИФМЕТИКА------------------------ */
/** *********************************************************************** */

/**
 * @class The arithmIntLong class - класс команд целочисленной арифметики.
 * Включает команду установки флагов и вычислительную команду.
 */

class arithmIntLong : public Command
{
    /**
     * @brief setFlags - команда установки флагов
     * @param processor - процессор необходим для доступа к регистру PSW
     */
    void setFlags(CPU &processor) noexcept;

    /**
     * @brief calculation - вычислительная команда
     * @param parametr1, @param parametr2 - значения, над которыми производятся вычисления
     * @return возвращается результат вычислений
     */
    virtual int32_t calculation(int parametr1, int parametr2) noexcept = 0;

public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/**
 * @class The addIntLong class - команда сложения целых чисел
 */

class addIntLong : public arithmIntLong
{
    /**
     * @brief calculation - команда сложения
     * @param parametr1 - первое слагаемое
     * @param parametr2 - второе слагаемое
     * @return возвращается сумма двух слагаемых
     */
    virtual int calculation(int parametr1, int parametr2) noexcept override final
    {
        return parametr1 + parametr2;
    }
};

/**
 * @class The subIntLong class - команда вычитания целых чисел
 */

class subIntLong: public arithmIntLong
{
    /**
     * @brief calculation - вычислительная команда
     * @param parametr1 - уменьшаемое
     * @param parametr2 - вычитаемое
     * @return возвращается разность двух чисел
     */
    virtual int calculation(int parametr1, int parametr2) noexcept override final
    {
        return parametr1 - parametr2;
    }
};

/**
 * @class The multIntLong class - команда умножения целых чисел
 */

class multIntLong : public arithmIntLong
{
    /**
     * @brief calculation - вычислительная команда
     * @param parametr1 - первый множитель
     * @param parametr2 - второй множитель
     * @return возвращается произведение множителей
     */
    virtual int calculation(int parametr1, int parametr2) noexcept override final
    {
        return parametr1 * parametr2;
    }
};

/**
 * @class The divIntLong class - команда деления целых чисел
 */

class divIntLong : public arithmIntLong
{
    /**
     * @brief calculation - вычислительная команда
     * @param parametr1 - делимое
     * @param parametr2 - делитель
     * @return возвращается частное от деления
     */
    virtual int calculation(int parametr1, int parametr2) noexcept override final
    {
        return parametr1 / parametr2;
    }
};

#endif // ARITMETICSNUMBERS_H

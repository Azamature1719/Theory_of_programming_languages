#include "jump.h"

/** *********************************************************************** */
/** -------------------------КОМАНДЫ ПЕРЕХОДОВ----------------------------- */
/** *********************************************************************** */

/**
 * @brief forwardJ - команда прямого перехода,
 * новое значение IP берётся из константного поля команды
 * @param processor - процессор. Доступ к процессору нужен чтобы изменить
 * регистр PSW (в котором хранится IP), который описан в классе процессора.
 * @return - ничего не возвращается.
 */

void Jump::forwardJ(CPU &processor)
{
    //! \brief address - адрес из команды
    address address = processor.get_cmdAR_address();

    //! Изменение IP
    //! \brief Для совершения корректного перехода, адрес перехода уменьшается на единицу
    //! в функции execute psw.ip увеличивается на единицу
    processor.PSW.IP = address - 1;
}

/**
 * @brief forwardIndJ - команда ПРЯМОГО АБСОЛЮТНОГО ПЕРЕХОДА,
 * адрес перехода берётся из памяти.
 * @param processor - процессор. Доступ к процессору нужен чтобы изменить
 * регистр PSW (в котором хранится IP), который описан в классе процессора.
 * @return - ничего не возвращается.
 */

void Jump::forwardIndJ (CPU &processor)
{
    //! \brief relAddress - адрес из константного поля команды
    address relAddress = processor.get_cmdAR_address();

    //! \brief address - адрес из памяти
    DataType address = processor.memory.pop_memory(relAddress);

    //! Изменение IP
    //! \brief Для совершения корректного перехода, адрес перехода уменьшается на единицу
    //! в функции execute psw.ip увеличивается на единицу
    processor.PSW.IP = address.address - 1;
}

/**
 * @brief forwardIndRegJ - косвенного регистрового перехода,
 * IP получается путём сложения адресов из регистров.
 * @param processor - процессор. Доступ к процессору нужен чтобы изменить
 * регистр PSW (в котором хранится IP), который описан в классе процессора.
 * @return - ничего не возвращается.
 */

void Jump::forwardIndRegJ (CPU &processor)
{
    //! \brief regN2 - номер второго регистра команды
    //! \brief regN3 - номер третьего регистра команды
    addressReg regN2 = processor.get_cmdU_r2(),
               regN3 = processor.get_cmdU_r3();

    //! \brief address1 - адрес, который лежит в первом регистре
    //! \brief address2 - адрес, который лежит во втором регистре
    address address1 = processor.addressRegister[regN2],
            address2 = processor.addressRegister[regN3];

    //! Изменение IP
    //! \brief Для совершения корректного перехода, адрес перехода уменьшается на единицу
    //! в функции execute psw.ip увеличивается на единицу
    processor.PSW.IP = address1 + address2 - 1;
}

/**
 * @brief relativeJ - команда относительного перехода,
 * новое значение IP получается путём сложения текущего адреса IP
 * с константным значением из команды.
 * @param processor - процессор. Доступ к процессору нужен потому что
 * регистр PSW (в котором хранится IP) описан в классе процессора.
 * @return - ничего не возвращается.
 */

void Jump::relativeJ (CPU &processor)
{
    //! \brief address - смещение из команды
    address address = processor.get_cmdAR_address();

    //! Изменение IP
    //! \brief Для совершения корректного перехода, адрес перехода уменьшается на единицу
    //! в функции execute psw.ip увеличивается на единицу
    processor.PSW.IP += address - 1;
}

/**
 * @brief Jump::operator() - команда перехода.
 * Осуществляет переход в соответствии с типом,
 * указанным в первом регистре команды
 * @param processor - класс процессора.
 * @return - ничего не возвращается.
 */

void Jump::operator()(CPU &processor) noexcept
{
    if (jumpTo(processor))
    {
        //! \brief type - тип совершаемого перехода
        addressReg type = processor.get_cmd_r1();
        switch (type)
        {
            //! Прямой переход
        case 0: forwardJ(processor);
            break;
            //! Прямой косвенный
        case 1: forwardIndJ(processor);
            break;
            //! Прямой косвенный регистровый
        case 2: forwardIndRegJ(processor);
            break;
            //! Относительный
        case 3: relativeJ(processor);
            break;
        }
    }
}

/**
 * @brief Uncoditional::jumpTo - команда безусловного перехода.
 * @return всегда истина: т.к. не осуществляется никакая проверка,
 * переход будет произведён в обязательном порядке.
 */

bool Uncoditional::jumpTo(CPU &processor) noexcept
{
    return true;
}

/**
 * @brief ConditionalZF::jumpTo - условный переход с проверкой флага нуля.
 * @param processor - процессор, процессор необходим для доступа к флагам PSW.
 * @return возвращает истину, если результат равен нулю, ложь - в противном случае
 */

bool ConditionalZF::jumpTo(CPU &processor) noexcept
{
    return (processor.PSW.ZF == 1);
}

bool ConditionalNOTzf::jumpTo(CPU &processor) noexcept
{
    return (processor.PSW.ZF == 0);
}

/**
 * @brief ConditionalSF::jumpTo - условный переход с проверкой знака результата.
 * @param processor - процессор, процессор необходим для доступа к флагам PSW.
 * @return возвращает истину, если результат отрицательный, ложь - если положительный
 */

bool ConditionalSF::jumpTo(CPU &processor) noexcept
{
    return (processor.PSW.SF == 1);
}

bool ConditionalNOTsf::jumpTo(CPU &processor) noexcept
{
    return (processor.PSW.SF == 0);
}

/**
 * @brief ToProgram::jumpTo - команда перехода к подпрограмме (прямой переход)
 * @param processor - процессор, адрес возврата запоминается в адресном регистре процессора.
 * @return возвращает всегда ложь, т.к. вызов подпрограммы осуществляется только с помощью
 * прямого перехода. Переход производится непосредственно из функции.
 */

bool ToProgram::jumpTo(CPU &processor) noexcept
{
    //! \brief regNum - номер адресного регистра из команды
    addressReg regNum = processor.get_cmd_r1();

    //! Сохранение адреса возврата в адресный регистр
    processor.addressRegister[regNum] = processor.PSW.IP + 1;

    //! Прямой переход к подпрограмме
    forwardJ(processor);
    return false;
}

/**
 * @brief Return::jumpTo - команда возврата из подпрограммы.
 * @param processor - процессор. Процессор необходим, т.к. IP хранится в классе процессора.
 * @return возвращает всегда ложь, т.к. IP изменяется непосредственно в функции.
 */

bool Return::jumpTo(CPU &processor) noexcept
{
    //! \brief regNum - номер адресного регистра, куда сохранён адрес возврата
    addressReg regNum = processor.get_cmd_r1();

    //! Изменение IP
    processor.PSW.IP = processor.addressRegister[regNum];
    return false;
}

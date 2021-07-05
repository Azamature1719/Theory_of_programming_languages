#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "cpu.h"

/** *********************************************************************** */
/** -----------------------АБСТРАКТНЫЙ КЛАСС КОМАНД------------------------ */
/** *********************************************************************** */

/**
 * @class The Command class - класс команд процессора
 */

class Command
{
public:
        virtual void operator() (CPU &processor) noexcept = 0;
        virtual ~Command() = 0;
};


#endif // COMMAND_H

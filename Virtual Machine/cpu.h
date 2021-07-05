#ifndef CPU_H
#define CPU_H

#include <cinttypes>
#include "memory.h"

//! \brief The opcode enum - коды операций процессора
/**
 * @brief команды лучше пронумеровать для удобства отладки
 */


class CPU
{
    #pragma pack(1)

    /**
     * @brief The ProgrammStateWord struct - регистр состояния процессора,
     * включает флаги состояния и счётчик команд (IP)
     */
    struct ProgrammStateWord
    {
        uint8_t ZF : 1; //! Флаг нуля
        uint8_t SF : 1; //! Флаг знака
        uint8_t reserved1 : 5;
        uint8_t reserved : 8; //! Резервные биты для флагов
        uint16_t IP = 0; //! Адрес выполняемой команды
    };
    #pragma pack(0)

    /**
     * @brief command - текущая выполняемая команда процессора
     */
    CommandType command;
    /**
     * @brief commandCPU - команды процессора, КОП-8 бит => 2^8 команд
     */
    class Command *commandCPU[256];

public:

    /**
     * @brief PSW - флаги состояния процессора и текущий адрес IP
     */
    ProgrammStateWord PSW;

    /**
     * @brief memory - память процессора, состоит из слов по 32 бита, размер адреса - 16 бит
     */
    Memory memory;

    /**
     * @brief addressRegister - адресные регистры - 256 шт. по 16 бит
     */
    address addressRegister[256] = {};

    CPU();
    ~CPU(){}

    /**
     * @brief get_cmdU_opcode
     * @return возвращается КОП
     */
    addressReg get_cmdU_opcode () const noexcept
    { return command.cmdU.opcode; }

    /**
     * @brief get_cmd_r1
     * @return возвращается первый регистр команды
     */
    addressReg get_cmd_r1() const noexcept
    { return command.cmdU.r1; }

    /**
     * @brief get_cmdU_r2
     * @return возвращается второй регистр команды
     */
    addressReg get_cmdU_r2() const noexcept
    { return command.cmdU.r2; }

    /**
     * @brief get_cmdU_r3
     * @return возвращается третий регистр команды
     */
    addressReg get_cmdU_r3() const noexcept
    { return command.cmdU.r3; }

    /**
     * @brief get_cmdAR_address - получение атрибута команды загрузки адресного регистра
     * @return возвращается значение константного поля команды
     */
    address get_cmdAR_address() const noexcept
    { return command.cmdAR.address; }

    /**
     * @brief reset - сброс флагов и обнуление адресных регистров
     */
    void reset() noexcept
    {
        PSW.ZF = 0;
        PSW.SF = 0;
        PSW.IP = 0;
        for(size_t i = 0; i < 256; ++i)
            addressRegister[i] = 0;
    }

    /**
     * @brief execute - команда запуска процессора
     */
    void execute() noexcept;
};
#endif  //CPU_H

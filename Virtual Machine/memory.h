#ifndef MEMORY_H
#define MEMORY_H

#include <cinttypes>
#include "structures.h"

class Memory
{
    //! @brief memory - память процессора (состоит из слов по 32 бита)
    MemoryData *memory;

public:

    /**
     * @brief Memory() - создание адресного пространства памяти
     */
    Memory() { memory = new MemoryData[65536];}

    //! Деструктор пространства памяти
    ~Memory() { delete [] memory;}

    /**
     * @brief pop_memory - возврат значения по данному адресу
     * @param address - адрес памяти, откуда необходимо вернуть значение
     * @return возвращает информацию по адресу в 32-битном типе DataType
     */
    DataType pop_memory (const address &address);

    /**
     * @brief push_memory-команда загрузки информации в память
     * @param type - тип информации: команда или значение
     * @param address - адрес загрузки в память
     */
    void push_memory (DataType &type, const address &address);
};
#endif // MEMORY_H

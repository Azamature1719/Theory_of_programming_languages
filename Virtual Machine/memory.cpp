#include <iostream>

#include "memory.h"

/**
 * @brief Memory::push_memory - команда загрузки значения в память
 * @param usedType - значение, загружаемое в память
 * @param address - адрес памяти, куда загружается значение
 */
void Memory::push_memory(DataType &usedType, const uint16_t &address)
{
    memory[address] = usedType.uintEl;
}

/**
 * @brief Memory::pop_memory - возврат значения из памяти по адресу
 * @param address - адрес памяти, по которому берётся значение
 * @return - значение из памяти возвращается как экземпляр union,
 * тип данных конкретизируется в вызываемой функции
 */
DataType Memory::pop_memory (const uint16_t &address)
{
    DataType neededData;
    neededData.uintEl = memory[address];
    return neededData;
}


#ifndef COMPARISON_H
#define COMPARISON_H
#include "command.h"


template< typename T>
class Comparison : public Command
{
public:
    virtual void operator()(CPU &processor) noexcept
    {
        addressReg r2 = processor.get_cmdU_r2(),
                r3 = processor.get_cmdU_r3();

        DataType parametr1 = processor.memory.pop_memory(processor.addressRegister[r2]),
          parametr2 = processor.memory.pop_memory(processor.addressRegister[r3]);

    }
};

#endif // COMPARISON_H

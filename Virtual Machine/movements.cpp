#include "movements.h"

/** *********************************************************************** */
/** ----------------------------КОМАНДЫ ПЕРЕСЫЛКИ-------------------------- */
/** *********************************************************************** */

/**
 * @brief uploadAddReg::operator () - команда загрузки адресного регистра.
 * @param processor - процессор. Доступ к процессору нужен потому что
 * адреса загружаются в регистры, которые расположены в классе процессора.
 * @return - ничего не возвращается.
 */

void uploadAddReg::operator()(CPU &processor) noexcept
{
    //! \brief regNum - номер адресного регистра
    addressReg regNum = processor.get_cmd_r1();

    //! \brief address - адрес памяти, куда надо загрузить значение регистра
    address address = processor.get_cmdAR_address();

    /** Загрузка адреса в регистр */
    processor.addressRegister[regNum] = address;
}

/**
 * @brief saveAddReg::operator() - команда сохранения адресного регистра в память.
 * @param processor - процессор. Доступ к процессору нужен чтобы загрузить
 * адреса из регистров в память процессора.
 * @return - ничего не возвращается.
 */

void saveAddReg::operator()(CPU &processor) noexcept
{
   //! \brief regNum - номер адресного регистра
   addressReg regNum = processor.get_cmd_r1();

   //! \brief address - адрес памяти, куда надо загрузить значение регистра
   address address = processor.get_cmdAR_address();

   /** Загрузка в память адреса из адресного регистра*/
   DataType addressToUpload;
   addressToUpload.uintEl = processor.addressRegister[regNum];
   processor.memory.push_memory(addressToUpload, address);
}

/**
 * @brief fromMemoryToReg::operator () - команда пересылки память-регистр
 * @param processor - процессор
 */
void fromMemoryToReg::operator()(CPU &processor) noexcept
{
    //! \brief regNum - номер адресного регистра
    addressReg regNum = processor.get_cmd_r1();

    //! \brief address - адрес памяти, откуда надо взять искомый адрес и загрузить в регистр
    address addressCMD = processor.get_cmdAR_address();

    /** Загрузка в регистра адреса из памяти*/
    address addresToTransmit = processor.memory.pop_memory(addressCMD).address;
    processor.addressRegister[regNum] = addresToTransmit;
}

/**
 * @brief exchAddReg::operator() - команда копирования/обмена адресными регистрами,
 * вид команды конкретизируется в первом регистре команды.
 * @param processor - процессор. Доступ к процессору нужен потому что
 * адресные регистры, над которыми производятся действия, расположены в классе процессора.
 * @return - ничего не возвращается.
 */

void exchAddReg::operator()(CPU &processor) noexcept
{
    //! \brief cmdType - тип команды - обмен/копирование
    //! \brief regNum1 - номер первого регистра
    //! \brief regNum2 - номер второго регистра
    addressReg cmdType = processor.get_cmd_r1(),
            regNum1 = processor.get_cmdU_r2(),
            regNum2 = processor.get_cmdU_r3();

    //! Копирование значений адресных регистров
    if(cmdType == 0)
    {
         processor.addressRegister[regNum2] = processor.addressRegister[regNum1];
    }

    //! Обмен значениями адресных регистров
    if(cmdType == 1)
    {
        address addBuf = processor.addressRegister[regNum1];
        processor.addressRegister[regNum1] = processor.addressRegister[regNum2];
        processor.addressRegister[regNum2] = addBuf;
    }
}

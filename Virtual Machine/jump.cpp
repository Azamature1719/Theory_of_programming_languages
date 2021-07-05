#include "jump.h"

/** *********************************************************************** */
/** -------------------------������� ���������----------------------------- */
/** *********************************************************************** */

/**
 * @brief forwardJ - ������� ������� ��������,
 * ����� �������� IP ������ �� ������������ ���� �������
 * @param processor - ���������. ������ � ���������� ����� ����� ��������
 * ������� PSW (� ������� �������� IP), ������� ������ � ������ ����������.
 * @return - ������ �� ������������.
 */

void Jump::forwardJ(CPU &processor)
{
    //! \brief address - ����� �� �������
    address address = processor.get_cmdAR_address();

    //! ��������� IP
    //! \brief ��� ���������� ����������� ��������, ����� �������� ����������� �� �������
    //! � ������� execute psw.ip ������������� �� �������
    processor.PSW.IP = address - 1;
}

/**
 * @brief forwardIndJ - ������� ������� ����������� ��������,
 * ����� �������� ������ �� ������.
 * @param processor - ���������. ������ � ���������� ����� ����� ��������
 * ������� PSW (� ������� �������� IP), ������� ������ � ������ ����������.
 * @return - ������ �� ������������.
 */

void Jump::forwardIndJ (CPU &processor)
{
    //! \brief relAddress - ����� �� ������������ ���� �������
    address relAddress = processor.get_cmdAR_address();

    //! \brief address - ����� �� ������
    DataType address = processor.memory.pop_memory(relAddress);

    //! ��������� IP
    //! \brief ��� ���������� ����������� ��������, ����� �������� ����������� �� �������
    //! � ������� execute psw.ip ������������� �� �������
    processor.PSW.IP = address.address - 1;
}

/**
 * @brief forwardIndRegJ - ���������� ������������ ��������,
 * IP ���������� ���� �������� ������� �� ���������.
 * @param processor - ���������. ������ � ���������� ����� ����� ��������
 * ������� PSW (� ������� �������� IP), ������� ������ � ������ ����������.
 * @return - ������ �� ������������.
 */

void Jump::forwardIndRegJ (CPU &processor)
{
    //! \brief regN2 - ����� ������� �������� �������
    //! \brief regN3 - ����� �������� �������� �������
    addressReg regN2 = processor.get_cmdU_r2(),
               regN3 = processor.get_cmdU_r3();

    //! \brief address1 - �����, ������� ����� � ������ ��������
    //! \brief address2 - �����, ������� ����� �� ������ ��������
    address address1 = processor.addressRegister[regN2],
            address2 = processor.addressRegister[regN3];

    //! ��������� IP
    //! \brief ��� ���������� ����������� ��������, ����� �������� ����������� �� �������
    //! � ������� execute psw.ip ������������� �� �������
    processor.PSW.IP = address1 + address2 - 1;
}

/**
 * @brief relativeJ - ������� �������������� ��������,
 * ����� �������� IP ���������� ���� �������� �������� ������ IP
 * � ����������� ��������� �� �������.
 * @param processor - ���������. ������ � ���������� ����� ������ ���
 * ������� PSW (� ������� �������� IP) ������ � ������ ����������.
 * @return - ������ �� ������������.
 */

void Jump::relativeJ (CPU &processor)
{
    //! \brief address - �������� �� �������
    address address = processor.get_cmdAR_address();

    //! ��������� IP
    //! \brief ��� ���������� ����������� ��������, ����� �������� ����������� �� �������
    //! � ������� execute psw.ip ������������� �� �������
    processor.PSW.IP += address - 1;
}

/**
 * @brief Jump::operator() - ������� ��������.
 * ������������ ������� � ������������ � �����,
 * ��������� � ������ �������� �������
 * @param processor - ����� ����������.
 * @return - ������ �� ������������.
 */

void Jump::operator()(CPU &processor) noexcept
{
    if (jumpTo(processor))
    {
        //! \brief type - ��� ������������ ��������
        addressReg type = processor.get_cmd_r1();
        switch (type)
        {
            //! ������ �������
        case 0: forwardJ(processor);
            break;
            //! ������ ���������
        case 1: forwardIndJ(processor);
            break;
            //! ������ ��������� �����������
        case 2: forwardIndRegJ(processor);
            break;
            //! �������������
        case 3: relativeJ(processor);
            break;
        }
    }
}

/**
 * @brief Uncoditional::jumpTo - ������� ������������ ��������.
 * @return ������ ������: �.�. �� �������������� ������� ��������,
 * ������� ����� ��������� � ������������ �������.
 */

bool Uncoditional::jumpTo(CPU &processor) noexcept
{
    return true;
}

/**
 * @brief ConditionalZF::jumpTo - �������� ������� � ��������� ����� ����.
 * @param processor - ���������, ��������� ��������� ��� ������� � ������ PSW.
 * @return ���������� ������, ���� ��������� ����� ����, ���� - � ��������� ������
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
 * @brief ConditionalSF::jumpTo - �������� ������� � ��������� ����� ����������.
 * @param processor - ���������, ��������� ��������� ��� ������� � ������ PSW.
 * @return ���������� ������, ���� ��������� �������������, ���� - ���� �������������
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
 * @brief ToProgram::jumpTo - ������� �������� � ������������ (������ �������)
 * @param processor - ���������, ����� �������� ������������ � �������� �������� ����������.
 * @return ���������� ������ ����, �.�. ����� ������������ �������������� ������ � �������
 * ������� ��������. ������� ������������ ��������������� �� �������.
 */

bool ToProgram::jumpTo(CPU &processor) noexcept
{
    //! \brief regNum - ����� ��������� �������� �� �������
    addressReg regNum = processor.get_cmd_r1();

    //! ���������� ������ �������� � �������� �������
    processor.addressRegister[regNum] = processor.PSW.IP + 1;

    //! ������ ������� � ������������
    forwardJ(processor);
    return false;
}

/**
 * @brief Return::jumpTo - ������� �������� �� ������������.
 * @param processor - ���������. ��������� ���������, �.�. IP �������� � ������ ����������.
 * @return ���������� ������ ����, �.�. IP ���������� ��������������� � �������.
 */

bool Return::jumpTo(CPU &processor) noexcept
{
    //! \brief regNum - ����� ��������� ��������, ���� ������� ����� ��������
    addressReg regNum = processor.get_cmd_r1();

    //! ��������� IP
    processor.PSW.IP = processor.addressRegister[regNum];
    return false;
}

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

void SCB_SetPriorityGrouping(u32 Copy_PriorityGrouping)
{
    SCB_AIRCR = Copy_PriorityGrouping;
}

Std_ReturnType MCAL_NVIC_EnableIRQ(IRQn_Type Copy_IRQn)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;
    
    if (Copy_IRQn < 32)
    {
        NVIC_ISER0 = (1 << Copy_IRQn);
        Local_FunctionStatus = E_OK;
    }
    else if (Copy_IRQn < 64)
    {
        NVIC_ISER1 = (1 << (Copy_IRQn - 32));
        Local_FunctionStatus = E_OK;
    }
    else if (Copy_IRQn < 96)
    {
        NVIC_ISER2 = (1 << (Copy_IRQn - 64));
        Local_FunctionStatus = E_OK;
    }
    else
    {
        Local_FunctionStatus = E_NOT_OK;
    }
    
    return Local_FunctionStatus;
}

Std_ReturnType MCAL_NVIC_DisableIRQ(IRQn_Type Copy_IRQn)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if (Copy_IRQn < 32)
    {
        NVIC_ICER0 = (1 << Copy_IRQn);
        Local_FunctionStatus = E_OK;
    }
    else if (Copy_IRQn < 64)
    {
        NVIC_ICER1 = (1 << (Copy_IRQn - 32));
        Local_FunctionStatus = E_OK;
    }
    else if (Copy_IRQn < 96)
    {
        NVIC_ICER2 = (1 << (Copy_IRQn - 64));
        Local_FunctionStatus = E_OK;
    }
    else
    {
        Local_FunctionStatus = E_NOT_OK;
    }
    
    return Local_FunctionStatus;
}

Std_ReturnType MCAL_NVIC_SetPendingIRQ(IRQn_Type Copy_IRQn)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if (Copy_IRQn < 32)
    {
        NVIC_ISPR0 = (1 << Copy_IRQn);
        Local_FunctionStatus = E_OK;
    }
    else if (Copy_IRQn < 64)
    {
        NVIC_ISPR1 = (1 << (Copy_IRQn - 32));
        Local_FunctionStatus = E_OK;
    }
    else if (Copy_IRQn < 96)
    {
        NVIC_ISPR2 = (1 << (Copy_IRQn - 64));
        Local_FunctionStatus = E_OK;
    }
    else
    {
        Local_FunctionStatus = E_NOT_OK;
    }
    
    return Local_FunctionStatus;
}

Std_ReturnType MCAL_NVIC_ClearPendingIRQ(IRQn_Type Copy_IRQn)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if (Copy_IRQn < 32)
    {
        NVIC_ICPR0 = (1U << Copy_IRQn);
        Local_FunctionStatus = E_OK;
    }
    else if (Copy_IRQn < 64)
    {
        NVIC_ICPR1 = (1U << (Copy_IRQn - 32));
        Local_FunctionStatus = E_OK;
    }
    else if (Copy_IRQn < 96)
    {
        NVIC_ICPR2 = (1U << (Copy_IRQn - 64));
        Local_FunctionStatus = E_OK;
    }

    return Local_FunctionStatus;
}

Std_ReturnType MCAL_NVIC_GetPendingIRQ(IRQn_Type Copy_IRQn, u8 *Copy_ReturnPendingFlag)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if (Copy_ReturnPendingFlag != NULL)
    {
        if (Copy_IRQn < 32)
        {
            if (NVIC_ISPR0 & (1U << Copy_IRQn))
            {
                *Copy_ReturnPendingFlag = 1;
            }
            else
            {
                *Copy_ReturnPendingFlag = 0;
            }
            Local_FunctionStatus = E_OK;
        }
        else if (Copy_IRQn < 64)
        {
            if (NVIC_ISPR1 & (1U << (Copy_IRQn - 32)))
            {
                *Copy_ReturnPendingFlag = 1;
            }
            else
            {
                *Copy_ReturnPendingFlag = 0;
            }
            Local_FunctionStatus = E_OK;
        }
        else if (Copy_IRQn < 96)
        {   
            if (NVIC_ISPR2 & (1U << (Copy_IRQn - 64)))
            {
                *Copy_ReturnPendingFlag = 1;
            }
            else
            {
                *Copy_ReturnPendingFlag = 0;
            }
            Local_FunctionStatus = E_OK;
        }
        else
        {
            Local_FunctionStatus = E_NOT_OK;
        }
    }

    return Local_FunctionStatus;
}

Std_ReturnType MCAL_NVIC_xSetPriority(IRQn_Type Copy_IRQn, u8 Copy_Priority)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if (Copy_IRQn < 0 || Copy_IRQn >= NUMBER_OF_INTERRUPTS)
    {
        return Local_FunctionStatus;
    }

    if (Copy_Priority <= NVIC_MAX_PRIORITY)
    {
        SCB_SetPriorityGrouping(NVIC_0GROUP_16SUB);

        u32 RegisterIndex = Copy_IRQn / 4;
        u32 BitPosition = (Copy_IRQn % 4) * 8;

        NVIC_IPR_BASE_ADDRESS[RegisterIndex] &= ~(0xFF << BitPosition);

        NVIC_IPR_BASE_ADDRESS[RegisterIndex] = (Copy_Priority << (BitPosition << 4));

        Local_FunctionStatus = E_OK;
    }

    return Local_FunctionStatus;
}

Std_ReturnType MCAL_NVIC_vSetPriority(IRQn_Type Copy_IRQn, u8 Copy_GroupPriority, u8 Copy_SubPriority)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;
    u8 NVIC_MAX_Group_Priority;
    u8 NVIC_MAX_Sub_Priority;

    #if (PRIORITY_GROUPING == NVIC_16GROUP_0SUB)
        NVIC_MAX_Group_Priority = 15;
        NVIC_MAX_Sub_Priority = NONE;
    #elif (PRIORITY_GROUPING == NVIC_8GROUP_2SUB)
        NVIC_MAX_Group_Priority = 7;
        NVIC_MAX_Sub_Priority = 1;
    #elif (PRIORITY_GROUPING == NVIC_4GROUP_4SUB)
        NVIC_MAX_Group_Priority = 3;
        NVIC_MAX_Sub_Priority = 3;
    #elif (PRIORITY_GROUPING == NVIC_2GROUP_8SUB)
        NVIC_MAX_Group_Priority = 1;
        NVIC_MAX_Sub_Priority = 7;
    #elif (PRIORITY_GROUPING == NVIC_0GROUP_16SUB)
        NVIC_MAX_Group_Priority = NONE;
        NVIC_MAX_Sub_Priority = 15;
    #else
        #error "Invalid PRIORITY_GROUPING value."
    #endif

    if (Copy_GroupPriority > NVIC_MAX_Group_Priority || Copy_SubPriority > NVIC_MAX_Sub_Priority)
    {
        return Local_FunctionStatus;
    }

    if (Copy_IRQn > NUMBER_OF_INTERRUPTS)
    {
        return Local_FunctionStatus;
    }

    SCB_SetPriorityGrouping(PRIORITY_GROUPING);

    u8 Local_Priority = (Copy_SubPriority | (Copy_GroupPriority << (PRIORITY_GROUPING - NVIC_16GROUP_0SUB) / 0x100));

    u32 RegisterIndex = Copy_IRQn / 4;
    u32 BitPosition = (Copy_IRQn % 4) * 8;
   
    u32 RegValue = NVIC_IPR_BASE_ADDRESS[RegisterIndex];
   
    RegValue &= ~(0xFF << BitPosition);

    RegValue |= (Local_Priority << BitPosition);
    
    NVIC_IPR_BASE_ADDRESS[RegisterIndex] = (RegValue << 4);

    return Local_FunctionStatus;
}

Std_ReturnType MCAL_NVIC_xGetPriority(IRQn_Type Copy_IRQn, u8 *Copy_Priority)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    if (Copy_IRQn > NUMBER_OF_INTERRUPTS)
    {
        return Local_FunctionStatus;
    }

    u8 RegisterIndex = Copy_IRQn / 4;
    u8 BitIndex = (Copy_IRQn % 4);
    u8 BitPosition = (Copy_IRQn % 4) * 8;

    u8 *PriorityRegister = (u8 *)&NVIC_IPR_BASE_ADDRESS[RegisterIndex];

    *Copy_Priority = (PriorityRegister[BitIndex] >> (BitPosition)) & 0xFF;

    Local_FunctionStatus = E_OK;

    return Local_FunctionStatus;
}

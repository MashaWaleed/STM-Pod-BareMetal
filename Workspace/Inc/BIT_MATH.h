#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/* Set any specific bit in a register or PORT */
#define SET_BIT(REG, BIT)  ((REG) |=  (1 << (BIT)))

/* Clear any specific bit in a register or PORT */
#define CLR_BIT(REG, BIT)  ((REG) &= ~(1 << (BIT)))

/* Toggle any specific bit in a register or PORT */
#define TOG_BIT(REG, BIT)  ((REG) ^=  (1 << (BIT)))

/* Get the value of a specific bit in a register or PIN */
#define GET_BIT(REG, BIT)  (((REG) >> (BIT)) & 1)

/* Check if a specific bit in a register or PIN is set */
#define BIT_IS_SET(REG, BIT)  ((REG) & (1 << (BIT)))

/* Check if a specific bit in a register or PIN is cleared */
#define BIT_IS_CLR(REG, BIT)  (!((REG) & (1 << (BIT))))

#endif

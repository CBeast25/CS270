#include "field.h"

/** @file field.c
 *  @brief You will modify this file and implement five functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. 
 * <p>
 * @author <b>Your name</b> goes here
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {
    int mask = 1;
    mask = mask << position;
    unsigned result = value & mask;
    return (result >> position);
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
    int mask = 1;
    mask = mask << position;
    unsigned result = value | mask; 
    return result;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
    int mask = 1;
    mask = mask << position;
    mask = ~mask;
    unsigned result = value & mask;
    return result;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, bool isSigned) {
    unsigned mask = 1;
    mask = ((mask << (hi-lo+1))-1) << lo;
    unsigned result = (value & mask) >> lo;
    if(isSigned == 1 && ((result >> (hi-lo)) == 1))
	return ~result + 1;
    return result;
}

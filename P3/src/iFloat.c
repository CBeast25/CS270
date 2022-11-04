#include "Debug.h"
#include "iFloat.h"

/** @file iFloat.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in iFloat.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Your name</b> goes here
 */

/* declaration for useful function contained in testFloat.c */
const char* getBinary (iFloat_t value);

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetSign (iFloat_t x) {
  return (x >> 15) & 1; /* implement this */
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetExp (iFloat_t x) {
  return (x >> 7) & 0x0FF; /* implement this */
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetVal (iFloat_t x) {
  iFloat_t temp = 0x0080 | (x & 0x007F);
  if(floatGetSign(x))
	  return temp = ~temp + 1;
  return temp;
}

/** @todo Implement based on documentation contained in iFloat.h */
void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t*exp, iFloat_t* val) {
	*sign = floatGetSign(x);
	*exp = floatGetExp(x);
	*val = floatGetVal(x);
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatLeftMost1 (iFloat_t bits) {
	int a = 0x8000;
	for(int i = 15; i >= 0; i--) {
		if((bits & a) != 0)
			return i;
		a = a >> 1;
	}
	return -1;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAbs (iFloat_t x) {
  return x & 0x7FFF;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatNegate (iFloat_t x) {
	if(floatLeftMost1(x)==-1)
		return 0;
	return x ^ 0x8000;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAdd (iFloat_t x, iFloat_t y) {
  debug("%s: bits of x (bfloat16)", getBinary(x)); // example only
  debug("%s: bits of y (bfloat16)", getBinary(y)); // example only
  if(floatLeftMost1(x)==-1) {
	  if(floatLeftMost1(y)==-1) {
		  return x;
	  }
	  return y;
  }
  if(floatLeftMost1(y)==-1) {
	  return x;
  }
  iFloat_t xsign;
  iFloat_t xexp;
  iFloat_t xmant;
  floatGetAll(x,&xsign,&xexp,&xmant);
  iFloat_t ysign;
  iFloat_t yexp;
  iFloat_t ymant;
  floatGetAll(y,&ysign,&yexp,&ymant);
  if(xexp > yexp) {
	  ymant = ymant >> (xexp - yexp);
  }
  else if(yexp > xexp) {
	  xmant = xmant >> (yexp - xexp);
	  xexp = yexp;
  }
  iFloat_t rmant = xmant + ymant;
  iFloat_t rsign = floatGetSign(rmant);
  if(rsign) 
	  rmant = ~rmant + 1;
  iFloat_t rexp;
  if((7-floatLeftMost1(rmant))<0) {
	rexp = xexp - (floatLeftMost1(rmant)-7);
	rmant = rmant >> (floatLeftMost1(rmant)-7);
  }
  else {
	rexp = xexp - (7-floatLeftMost1(rmant));
	rmant = rmant << (7-floatLeftMost1(rmant));
  }
  return (rsign << 15) | (rexp << 7) | (rmant & 0x007F);
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatSub (iFloat_t x, iFloat_t y) {
  return floatAdd(x, floatNegate(y));
}


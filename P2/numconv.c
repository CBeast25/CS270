/**
 *  @author  your name goes here
 */

#include <stdio.h>

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int_to_char (int value, int radix) {
  if(value>=radix || value<0)
    return '?';
  if(value<10)
    return value+'0';
  return value + 'A' - 10;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char_to_int (char digit, int radix) {
  int value;
	if(digit>90)
		value = digit-'a'+10;
	else if(digit>57)
		value = digit-'A'+10;
  else
    value = digit-'0';
  if(value>=radix || value<0)
    return -1;
  return value;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void div_rem (int numerator, int divisor, int* remainder, int* quotient) {
  *remainder = numerator%divisor;
  *quotient = numerator/divisor;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii_to_int (int valueOfPrefix, int radix) {
  char c = getchar();
  if(c == '\n')
   return valueOfPrefix;
  return ascii_to_int(valueOfPrefix*radix+char_to_int(c,radix),radix);
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int_to_ascii (int value, int radix) {
  if(value!=0) {
    int_to_ascii(value/radix,radix);
    putchar(int_to_char(value%radix,radix));
  }
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double frac_to_double (int radix) {
  char c = getchar();
  if(c == '\n')
    return 0;
  return ((double)char_to_int(c,32))/radix + frac_to_double(radix)/radix;
}


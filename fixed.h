#ifndef _FIXED_H
#define _FIXED_H

// Bit length of the decimal part, change it to change the precision :
#define DB 12

#define MOD(x, y) ((x)<0 ? (y)+(x)%(y) : (x)%(y))

typedef int fix;



// Fixed point manipulations functions and macros :
char* fixtostr (fix n, char* string);

fix ftofix(float f);

float fixtof(fix f);

#define FIX(x) ((x)<<DB)

#define UNFIX(x) ((x)>>DB)

fix fdiv(fix x, fix y);

fix fmul(fix x, fix y);

fix fsin(fix a);
fix fcos(fix a);
fix ftan(fix a);


#endif // _FIXED_H

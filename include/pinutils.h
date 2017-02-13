#ifndef PINUTILS_H
 #define PINUTILS_H

 #define _CONCAT(a,b) a##b
 #define PORT(x) _CONCAT(PORT,x)
 #define PIN(x) _CONCAT(PIN,x)
 #define DDR(x) _CONCAT(DDR,x)
 #define set(a,b) a|=(1<<b)
 #define clr(a,b) a&=(~(1<<b))
 #define chk(a,b) a&(1<<b)	

#endif

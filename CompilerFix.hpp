#ifndef COMPILERFIX_H
#define COMPILERFIX_H

#ifndef NULL
#ifdef __cplusplus
#define NULL nullptr
#else
#define NULL ((void*)0)
#endif
#endif

#include <stdio.h>
#include <stdarg.h>

#endif // COMPILERFIX_H

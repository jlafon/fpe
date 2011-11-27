/* File: testfpe.c
 * Author: Jharrod LaFon
 * Purpose: Test floating point exception capability
*/

/* Define FENV_H to use a different header. */
#ifdef FENV_H
    #include FENV_H
#else
    #include <fenv.h>
#endif

/* Define FLOAT_H to use a different header. */
#ifdef FLOAT_H
    #include FLOAT_H
#else   
    #include<float.h>
#endif

/* Define MATH_H for a custom math header. */
#ifdef MATH_H
    #include MATH_H
#else
    #include<math.h>
#endif
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
/* Get access to floating-point status flags. */
#pragma STDC FENV_ACCESS ON

/* Clear exceptions */
#define CLEAR_FLAGS (void)feclearexcept( FE_ALL_EXCEPT )

/* Raise all exceptions */
#define RAISE_ALL (void)feraiseexcept( FE_ALL_EXCEPT )

#ifdef __cplusplus
using namespace std;
#endif

int testflags()
{
    int flags = fetestexcept( FE_ALL_EXCEPT );
    if( flags )
        printf("Warning: Some flags already set, they will be cleared.");
    return flags;
}
int raisealltest()
{
    RAISE_ALL;
    int flags = fetestexcept( FE_ALL_EXCEPT );
    
    if ( flags == FE_ALL_EXCEPT )
        return 0;
    else
        return 1;
}

int clearalltest()
{
    RAISE_ALL;
    CLEAR_FLAGS;
    int flags = fetestexcept( FE_ALL_EXCEPT );
    if(!flags)
        return 0;
    else
        return 1;
}
int testi2fconv()
{
    
    return 0;
}
int invalidoptest()
{
    CLEAR_FLAGS;
    double val = -2.7f;
    val = sqrt(val);
    int flags = fetestexcept( FE_INVALID );
    return !( flags & FE_INVALID ); 
}
int divbyzerotest()
{
    CLEAR_FLAGS;
    double val = 0.0;
    double result = 0x55;
    result = result/val;
    int flags = fetestexcept( FE_DIVBYZERO );
    return !( flags & FE_DIVBYZERO );
}
int overflowtest()
{
    CLEAR_FLAGS;
    double val = 1.79E+308;
    val = pow(val,2);
    int flags = fetestexcept( FE_OVERFLOW );
    return !( flags & FE_OVERFLOW );
}
int underflowtest()
{
    CLEAR_FLAGS;
    double val = 1e-308 * 3.141;
    int i = 0;
    for(i = 0; i < 4; ++i)
        val /= 100000;
    int flags = fetestexcept( FE_UNDERFLOW );
    return !( flags & FE_UNDERFLOW );
}
int printmachineinfo()
{
    int float_precision = 20;
    int double_precision = 30;
    int longdouble_precision = 40;
    printf("===============================================================================\n");
    printf("                     Environment Floating Point Values\n");
    printf("===============================================================================\n");
#ifndef __STDC_IEC_559__ 
    #error "IEEE 754 Floating point required!"
#endif
#ifdef __STRICT_ANSI__
#else
    printf("Warning: This should be compiled with -ansi.\n");
#endif
#ifdef __x86_64
    if(__x86_64 == 1)
        printf("Architecture:\t\t\t\t\t\t64 bit\n");
#endif
#ifdef __i386
    if(__i386 == 1)
        printf("Architecture:\t\t\t\t\t\t32 bit\n");
#endif
#ifdef __FINITE_MATH_ONLY__
    if(__FINITE_MATH_ONLY__ == 1)
        printf("Warning: -finite-math-only enabled, this is not ISO compliant\n");
#endif
#ifdef __FLT_EVAL_METHOD__
    if(__FLT_EVAL_METHOD__ == 0)
        ;
    else if(__FLT_EVAL_METHOD__ == 1)
        printf("Warning: float_t and double_t are the same size.\n");
    else if(__FLT_EVAL_METHOD__ == 2)
        printf("Warning: float_t and double_t are long doubles.\n");
    else
        printf("Warning: Unrecognized value for __FLT_EVAL_METHOD.\n");
#endif
#ifdef __DECIMAL_BID_FORMAT__
    if(__DECIMAL_BID_FORMAT__ == 1)
        printf("IEEE 754 Numbers are encoded are binary encoded.\n");
    else if (__DECIMAL_BID_FORMAT__ == 0)
        printf("IEEE 754 Numbers are encoded are decimal encoded.\n");
#endif
#ifdef __DBL_DIG__
    printf("Digits of precision for double: \t\t\t%d\n", __DBL_DIG__);
    double_precision = __DBL_DIG__;
#endif
#ifdef __FLT_DIG__
    printf("Digits of precision for float:  \t\t\t%d\n", __FLT_DIG__);
    float_precision = __FLT_DIG__;
#endif
#ifdef __LDBL_DIG__
    printf("Digits of precision for long double: \t\t\t%d\n", __LDBL_DIG__);
    longdouble_precision = __LDBL_DIG__;
#endif
#ifdef __LDBL_MIN_10_EXP__
    printf("Minimum value of long double exponent: 	\t\t%d\n", __LDBL_MIN_10_EXP__);
#endif
#ifdef __FLT_MIN_10_EXP__
    printf("Minimum value of double exponent: \t\t\t%d\n", __DBL_MIN_10_EXP__);
#endif
#ifdef __FLT_MIN_10_EXP__
    printf("Minimum value of float exponent:  \t\t\t%d\n", __FLT_MIN_10_EXP__);
#endif

#ifdef __LDBL_MAX_10_EXP__
    printf("Maximum value of long double exponent: 	\t\t%d\n", __LDBL_MAX_10_EXP__);
#endif
#ifdef __DBL_MAX_10_EXP__
    printf("Maximum value of double exponent: 	\t\t%d\n", __DBL_MAX_10_EXP__);
#endif
#ifdef __FLT_MAX_10_EXP__
    printf("Maximum value of float exponent: \t\t\t%d\n", __FLT_MAX_10_EXP__);
    
#endif
#ifdef __LDBL_MANT_DIG__
    printf("Number of base digits in mantissa of long double: \t%d\n", __LDBL_MANT_DIG__);
#endif
#ifdef __DBL_MANT_DIG__
    printf("Number of base digits in mantissa of double: \t\t%d\n", __DBL_MANT_DIG__);
#endif
#ifdef __FLT_MANT_DIG__
    printf("number of base digits in mantissa of float:  \t\t%d\n", __FLT_MANT_DIG__);
#endif

#ifdef __LDBL_EPSILON__
    printf("Machine epsilon for long double: \t\t\t%.*Le\n", longdouble_precision,__LDBL_EPSILON__);
#endif
#ifdef __DBL_EPSILON__
    printf("Machine epsilon for double: \t\t\t\t%.*e\n", double_precision,__DBL_EPSILON__);
#endif
#ifdef __FLT_EPSILON__
    printf("Machine epsilon for float: 	\t\t\t%.*e\n", float_precision,__FLT_EPSILON__);
#endif
#ifdef __FLT_RADIX__
    printf("Radix of float representation: 	\t\t\t%d\n", __FLT_RADIX__);
    #ifdef __LDBL_MAX_EXP__
        printf("Maximum value of long double exponent with base %d:      %d\n",__FLT_RADIX__,__LDBL_MAX_EXP__);
    #endif
    #ifdef __DBL_MAX_EXP__
        printf("Maximum value of double exponent with base %d:		%d\n",__FLT_RADIX__,__DBL_MAX_EXP__);
    #endif
    #ifdef __FLT_MAX_EXP__
        printf("Maximum value of float exponent with base %d:		%d\n",__FLT_RADIX__,__FLT_MAX_EXP__);
    #endif
    #ifdef __LDBL_MIN_EXP__
        printf("Minimum value of long double exponent with base %d:     %d\n",__FLT_RADIX__,__LDBL_MIN_EXP__);
    #endif
    #ifdef __DBL_MIN_EXP__
        printf("Minimum value of double exponent with base %d:		%d\n",__FLT_RADIX__,__DBL_MIN_EXP__);
    #endif
    #ifdef __FLT_MIN_EXP__
        printf("Maximum value of float exponent with base %d:		%d\n",__FLT_RADIX__,__FLT_MIN_EXP__);
    #endif
#endif
#ifdef __DBL_MAX__
    printf("Maximum value for double: \t\t\t\t%.*e\n", double_precision,__DBL_MAX__);
#endif
#ifdef __FLT_MAX__
    printf("Maximum value for float : \t\t\t\t%.*e\n", double_precision,__FLT_MAX__);
#endif

#ifdef __DBL_MIN__
    printf("Minimum value for double: \t\t\t\t%.*e\n", double_precision,__DBL_MIN__);
#endif
#ifdef __FLT_MIN__
    printf("Minimum value for float : \t\t\t\t%.*e\n", float_precision,__FLT_MIN__);
#endif
#ifdef __FLT_HAS_DENORM__
    if(__FLT_HAS_DENORM__ == 1)
        printf("Denormalized floating point values are supported.\n");
    else if (__FLT_HAS_DENORM__ == 0)
        printf("Denormalized floating point values are not supported.\n");
#endif
#ifdef __LDBL_DENORM_MIN__
    printf("Minimum denormalized long double: \t\t\t%.*Le\n", longdouble_precision, __LDBL_DENORM_MIN__);
#endif
#ifdef __DBL_DENORM_MIN__
    printf("Minimum denormalized double: \t\t\t\t%.*e\n", double_precision, __DBL_DENORM_MIN__);
#endif
#ifdef __FLT_DENORM_MIN__
    printf("Minimum denormalized float: \t\t\t\t%.*e\n", float_precision, __FLT_DENORM_MIN__);
#endif
#ifdef __LDBL_DENORM_MAX__
    printf("Maximum denormalized long double: \t\t\t\t%.*Le\n", longdouble_precision, __LDBL_DENORM_MAX__);
#endif
#ifdef __DBL_DENORM_MAX__
    printf("Maximum denormalized double: \t\t\t\t%.*e\n", double_precision, __DBL_DENORM_MAX__);
#endif
#ifdef __FLT_DENORM_MAX__
    printf("Maximum denormalized float: \t\t\t\t%.*e\n", float_precision, __FLT_DENORM_MAX__);
#endif
#ifdef __LDBL_HAS_INFINITY__
    if(__LDBL_HAS_INFINITY__ == 1)
        printf("Long doubles support infinity.\n");
    else if (__LDBL_HAS_INFINITY__ == 0)
        printf("Long doubles do not support infinity.\n");
#endif
#ifdef __DBL_HAS_INFINITY__
    if(__DBL_HAS_INFINITY__ == 1)
        printf("Doubles support infinity.\n");
    else if (__DBL_HAS_INFINITY__ == 0)
        printf("Doubles do not support infinity.\n");
#endif
#ifdef __FLT_HAS_INFINITY__
    if(__FLT_HAS_INFINITY__ == 1)
        printf("Floats support infinity.\n");
    else if (__FLT_HAS_INFINITY__ == 0)
        printf("Floats do not support infinity.\n");
#endif
#ifdef __LDBL_HAS_QUIET_NAN__
    if(__LDBL_HAS_QUIET_NAN__ == 1)
        printf("Long doubles support quiet NaN.\n");
    else if(__LDBL_HAS_QUIET_NAN__ == 0)
        printf("Long doubles do not support quiet NaN.\n");
#endif
#ifdef __DBL_HAS_QUIET_NAN__
    if(__DBL_HAS_QUIET_NAN__ == 1)
        printf("Doubles support quiet NaN.\n");
    else if(__DBL_HAS_QUIET_NAN__ == 0)
        printf("Doubles do not support quiet NaN.\n");
#endif
#ifdef __FLT_HAS_QUIET_NAN__
    if(__FLT_HAS_QUIET_NAN__ == 1)
        printf("Floats support quiet NaN.\n");
    else if(__FLT_HAS_QUIET_NAN__ == 0)
        printf("Floats do not support quiet NaN.\n");
#endif
#ifdef __FLT_ROUNDS__
    if(__FLT_ROUNDS__ == -1)
        printf("Warning: Cannot determine float rounding mode.\n");
    else if (__FLT_ROUNDS__ == 0)
        printf("Floating point values round toward zero.\n");
    else if (__FLT_ROUNDS__ == 1)
        printf("Floating point values round toward nearest.\n");
    else if (__FLT_ROUNDS__ == 2)
        printf("Floating point values round toward +infinity.\n");
    else if (__FLT_ROUNDS__ == 3)
        printf("Floating point values round toward -infinity.\n");
    else
        printf("Warning: Cannot determine float rounding mode.\n");
#endif
return 0;
}
int main(int argc, char *argv[])
{
    if(argc > 1)
        if(!strncmp(argv[1],"-i",2))
            printmachineinfo();
  
    int fd = open("/dev/null", O_WRONLY);
    dup2(2, fd);
    testflags();
    printf("===============================================================================\n");
    printf("                       Floating point exception tests\n");
    printf("===============================================================================\n");

    printf("Raising All flags: 	\t\t%s\n", ((raisealltest() == 0)?"PASS":"FAIL"));
    printf("Clearing All flags: \t\t\t%s\n", ((clearalltest() == 0)?"PASS":"FAIL"));
    printf("Testing invalid operation exception: \t%s\n", ((invalidoptest() == 0)?"PASS":"FAIL"));
    printf("Testing division by zero exception: \t%s\n", ((divbyzerotest() == 0)?"PASS":"FAIL"));
    printf("Testing overflow exception: \t\t%s\n", ((overflowtest() == 0)?"PASS":"FAIL"));
    printf("Testing underflow exception: \t\t%s\n", ((underflowtest() == 0)?"PASS":"FAIL"));
    close(fd);

    return 0;
}


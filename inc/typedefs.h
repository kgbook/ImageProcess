#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

typedef unsigned char           KG_U8;
typedef unsigned short          KG_U16;
typedef unsigned int            KG_U32;
typedef signed char             KG_S8;
typedef short                   KG_S16;
typedef int                     KG_S32;
typedef char                    KG_CHAR;
typedef KG_S32                  KG_HANDLE;
typedef unsigned long           KG_SIZE_T;
typedef long           			KG_LONG;
typedef float               	KG_FLOAT;
typedef double                  KG_DOUBLE;

#ifndef _M_IX86
    typedef unsigned long long  KG_U64;
    typedef long long           KG_S64;
#else
    typedef __int64             KG_U64;
    typedef __int64             KG_S64;
#endif

typedef enum {
    KG_FALSE = 0,
    KG_TRUE  = 1,
} KG_BOOL;

#define 			KG_VOID              	void
#define 			KG_INVALID_HANDLE 		(-1)
#define 			KG_SUCCESS  			(0)
#define 			KG_FAILURE  			(-1)

#define				PRINT_ERR
#ifdef				PRINT_ERR
	#define			print_err(format, args...)				printf("[err][%s:%d]"format"\n", __func__, __LINE__, ##args)
#else
	#define			print_err(format, args...)
#endif

#define	  KG_ASSERT(expr)\
do\
{\
	if (!(expr))\
	{\
		print_err("%s", #expr);\
		return ;\
	}\
}while(0)

#define	  KG_ASSERT_RET(expr, ret)\
do\
{\
	if (!(expr))\
	{\
		print_err("%s", #expr);\
		return ret;\
	}\
}while(0)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

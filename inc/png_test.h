#ifndef _PNG_TEST_H_
#define _PNG_TEST_H_

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

#ifndef NULL
    #define 		NULL    				0L
#endif

#define 			KG_VOID              void
#define 			KG_INVALID_HANDLE 		(-1)
#define 			KG_NULL     			0L
#define 			KG_NULL_PTR 			0L
#define 			KG_SUCCESS  			0
#define 			KG_FAILURE  			(-1)

//#define				PRINT_DEBUG
#define					PRINT_ERR

#ifdef				PRINT_DEBUG
	#define 		print_debug(format, args...)			printf("[debug][%s]"format"\n", __func__, ##args);
#else
	#define			print_debug(format, args...)
#endif

#ifdef				PRINT_ERR
	#define			print_err(format, args...)				printf("[err][%s]"format"\n", __func__, ##args);
#else
	#define			print_err(format, args...)
#endif

#define 			PNG_HEADER_LEN					(8)

typedef struct
{
	KG_U32 u32Width;
	KG_U32 u32Height;
	KG_U32 u32Len;
}PNG_S_DIM;

#endif

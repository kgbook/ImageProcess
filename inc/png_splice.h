#ifndef _PNG_SPLICE_H_
#define _PNG_SPLICE_H_

#include "typedefs.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

typedef struct
{
    KG_CHAR *pscAddr;
	KG_U32 u32Width;
	KG_U32 u32Height;
	KG_U32 u32Len;
	KG_CHAR *acPath;
    KG_CHAR scToken;
}PNG_S_DATA;

typedef struct tagPNG_S_NODE
{
    struct tagPNG_S_NODE *prev;
    struct tagPNG_S_NODE *next;
    PNG_S_DATA stData;
}PNG_S_NODE;

typedef struct
{
    PNG_S_NODE stList;
    KG_U32 u32Cnt;
}PNG_S_MOD;

//#define				PRINT_DEBUG
#define					PRINT_INFO

#ifdef				PRINT_DEBUG
	#define 		print_debug(format, args...)			printf("[debug][%s:%d]"format"\n", __func__, __LINE__, ##args);
#else
	#define			print_debug(format, args...)
#endif

#ifdef				PRINT_INFO
	#define 		print_info(format, args...)			printf("[info][%s:%d]"format"\n", __func__, __LINE__, ##args);
#else
	#define			print_info(format, args...)
#endif

#define 			PNG_HEADER_LEN					(8)
#define				PNG_MAX_NUM						(0x10)

#define				PNG_RES_PATH					"./res"

#define				SAFE_FREE(ptr)\
do\
{\
	if (NULL != ptr)\
	{\
		free(ptr);\
		ptr = NULL;\
	}\
}while(0)


KG_U32 png_to_rgba32(PNG_S_DATA *pstData, KG_CHAR *pszPath);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

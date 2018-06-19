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

#define              KB	        (1<<10)
#define	             MB         (1<<20)
#define              GB         (1<<30)

//#define			PRINT_DEBUG
#define				PRINT_INFO

#ifdef				PRINT_DEBUG
	#define 		print_debug(format, args...)		printf("[debug][%s:%d]"format"\n", __func__, __LINE__, ##args);
#else
	#define			print_debug(format, args...)
#endif

#ifdef				PRINT_INFO
	#define 		print_info(format, args...)			printf("[info][%s:%d]"format"\n", __func__, __LINE__, ##args);
#else
	#define			print_info(format, args...)
#endif

#define 			PNG_HEADER_LEN					    (8)

#define				PNG_RES_PATH					    "./res"

#define				SAFE_FREE(ptr)\
do\
{\
	if (NULL != ptr)\
	{\
		free(ptr);\
		ptr = NULL;\
	}\
}while(0)

#define				SAFE_FCLOSE(fp)\
do\
{\
    if (NULL != fp)\
    {\
        fclose(fp);\
        fp = NULL;\
    }\
}while(0)

#define				SAFE_CLOSE(fd)\
do\
{\
    if (fd >= 0)\
    {\
        close(fp);\
        fd = -1;\
    }\
}while(0)

#define    MAX(a, b)    ((a) >= (b) ? (a) : (b))

KG_S32 png_to_rgba32(PNG_S_DATA *pstData, KG_CHAR *pszPath);
KG_S32 rgba32_splice(PNG_S_MOD *pstMod, KG_CHAR *acStr, KG_CHAR *acOutBuf, KG_S32 *ps32Len);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

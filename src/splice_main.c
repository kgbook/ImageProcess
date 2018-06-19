#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "png_splice.h"
#include "png_list.h"
#include "list_api.h"
#include "backtrace.h"

#define     OUTPUT_RGBA_FILENAME     "out.rgba32"

static PNG_S_DATA m_stImg[] = {
    {.acPath = PNG_RES_PATH"/0.png", .scToken = '0'},
    {.acPath = PNG_RES_PATH"/1.png", .scToken = '1'},
    {.acPath = PNG_RES_PATH"/2.png", .scToken = '2'},
    {.acPath = PNG_RES_PATH"/3.png", .scToken = '3'},
    {.acPath = PNG_RES_PATH"/4.png", .scToken = '4'},
    {.acPath = PNG_RES_PATH"/5.png", .scToken = '5'},
    {.acPath = PNG_RES_PATH"/6.png", .scToken = '6'},
    {.acPath = PNG_RES_PATH"/7.png", .scToken = '7'},
    {.acPath = PNG_RES_PATH"/8.png", .scToken = '8'},
    {.acPath = PNG_RES_PATH"/9.png", .scToken = '9'},
    {.acPath = PNG_RES_PATH"/colon.png", .scToken = ':'},
    {.acPath = PNG_RES_PATH"/point.png", .scToken = '.'},
    {.acPath = PNG_RES_PATH"/line.png", .scToken = '-'},
    {.acPath = PNG_RES_PATH"/C.png", .scToken = 'C'},
    {.acPath = PNG_RES_PATH"/F.png", .scToken = 'F'},
    {.acPath = PNG_RES_PATH"/m.png", .scToken = 'm'},
};

static KG_U32 m_u32ImgCnt = sizeof(m_stImg) / sizeof(m_stImg[0]);

KG_S32 main(KG_S32 argc, KG_CHAR **argv)
{
    PNG_S_MOD stMod;
    KG_U32 u32Index;
    KG_S32 s32Len;
    KG_S32 s32Ret;
    KG_CHAR *acStr = "2018-06-19";
    FILE *fpRgb = NULL;
    KG_CHAR *m_acData = NULL;
    struct sigaction stSigAction;

    stSigAction.sa_flags = SA_SIGINFO;
    stSigAction.sa_sigaction = (KG_VOID *)DebugBacktrace;
    sigaction(SIGSEGV, &stSigAction, NULL);

    s32Ret = png_list_init(&stMod);
    KG_ASSERT_RET(KG_SUCCESS == s32Ret, KG_FAILURE);
    
    for (u32Index = 0; u32Index < m_u32ImgCnt; u32Index++)
    {
        if (KG_SUCCESS != png_to_rgba32(&m_stImg[u32Index], m_stImg[u32Index].acPath))
	    {
            print_err("png_to_rgba32(, %s) failed!", m_stImg[u32Index].acPath);
            goto error_handle;
	    }

        s32Ret = png_list_insert(&stMod, &m_stImg[u32Index]);
        if (KG_SUCCESS != s32Ret)
        {
            print_err("%s parse failed!", m_stImg[u32Index].acPath);
            goto error_handle;
        }
    }

#ifdef PRINT_DEBUG    
    png_list_query(&stMod);
#endif
    
    m_acData = (KG_CHAR *)malloc(3 * MB);
    if (NULL == m_acData)
    {
        print_err("malloc() failed!");
        goto error_handle;
    }

    if (KG_SUCCESS != rgba32_splice(&stMod, acStr, m_acData, &s32Len))
    {
        print_err("rgba32_splice(, %s, ) failed!", acStr);
        goto error_handle;
    }

    if (NULL == (fpRgb = fopen(OUTPUT_RGBA_FILENAME, "w")))
    {
	    print_err("failed when fopen().");
        goto error_handle;
    }

    fwrite(m_acData, 1, s32Len, fpRgb);
    SAFE_FCLOSE(fpRgb);
    SAFE_FREE(m_acData);
	
    s32Ret = png_list_deinit(&stMod);
    KG_ASSERT_RET(KG_SUCCESS == s32Ret, KG_FAILURE);
    
    return KG_SUCCESS;

error_handle:
    SAFE_FCLOSE(fpRgb);
    SAFE_FREE(m_acData);
    s32Ret = png_list_deinit(&stMod);
    KG_ASSERT_RET(KG_SUCCESS == s32Ret, KG_FAILURE);
    
    return KG_FAILURE; 
}

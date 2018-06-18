#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "png_splice.h"
#include "png_list.h"
#include "backtrace.h"

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
};

static KG_U32 m_u32ImgCnt = sizeof(m_stImg) / sizeof(m_stImg[0]);

KG_S32 main(KG_S32 argc, KG_CHAR **argv)
{
    PNG_S_MOD stMod;
    KG_U32 u32Index;
    KG_S32 s32Ret;
	//FILE *fpRgb = NULL;
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
		    return KG_FAILURE;
	    }

        s32Ret = png_list_insert(&stMod, &m_stImg[u32Index]);
        if (KG_SUCCESS != s32Ret)
        {
            print_err("%s parse failed!", m_stImg[u32Index].acPath);
            return KG_FAILURE;
        }

        s32Ret = png_list_query(&stMod);
        KG_ASSERT_RET(KG_SUCCESS == s32Ret, KG_FAILURE);
    }

    s32Ret = png_list_query(&stMod);
    KG_ASSERT_RET(KG_SUCCESS == s32Ret, KG_FAILURE);

    s32Ret = png_list_deinit(&stMod);
    KG_ASSERT_RET(KG_SUCCESS == s32Ret, KG_FAILURE);

#if 0
	if (NULL == (fpRgb = fopen("png.rgb8888", "w")))
	{
		print_err("failed when fopen().");
		return KG_FAILURE;
	}

	acFilename = argv[1];	
	memset(&m_stImg[u32Index].pscAddr, 0, sizeof(m_stImg[u32Index].pscAddr));

	printf("width = %u\n", m_stImg[u32Index].pscAddr.u32Width);
	printf("height = %u\n", m_stImg[u32Index].pscAddr.u32Height);
	printf("len = %u\n", m_stImg[u32Index].pscAddr.u32Len);

	fwrite(acImgData, 1, m_stImg[u32Index].pscAddr.u32Len, fpRgb);
	if (NULL != fpRgb)
	{
		fclose(fpRgb);
		fpRgb = NULL;
	}
#endif	
	return KG_SUCCESS;
}

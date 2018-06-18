#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "typedefs.h"
#include "png_splice.h"
#include "png_list.h"
#include "list.h"

KG_S32 png_list_query(PNG_S_MOD *pstMod)
{
    PNG_S_NODE *pstItem = NULL;
    PNG_S_NODE *pstHead = NULL;
    PNG_S_DATA *pstData = NULL;

    KG_ASSERT_RET(NULL != pstMod, KG_FAILURE);

    pstHead = &pstMod->stList;
    FOR_EACH_LIST_ITEM(pstItem, pstHead)
    {
        pstData = &pstItem->stData;
        print_info("Token:%c, width:%u, height:%u, len:%u", pstData->scToken, pstData->u32Width, pstData->u32Height, pstData->u32Len);
    }
    print_info("total:%u", pstMod->u32Cnt);

    return KG_SUCCESS;
}

KG_S32 png_list_insert(PNG_S_MOD *pstMod, PNG_S_DATA *pstData)
{
    PNG_S_NODE *pstNode = NULL;
    PNG_S_NODE *pstHead = NULL;

    KG_ASSERT_RET(NULL != pstMod, KG_FAILURE);
    KG_ASSERT_RET(NULL != pstData, KG_FAILURE);
    KG_ASSERT_RET(NULL != pstData->pscAddr, KG_FAILURE);

    pstNode = (PNG_S_NODE *)malloc(sizeof(PNG_S_NODE));
    KG_ASSERT_RET(NULL != pstNode, KG_FAILURE);

    LIST_INIT(pstNode);
    memcpy(&pstNode->stData, pstData, sizeof(PNG_S_DATA));

    pstHead = &pstMod->stList;
    LIST_ADD_AFTER(pstNode, pstHead->next);
    pstMod->u32Cnt++;

    return KG_SUCCESS;
}

PNG_S_NODE *png_list_search(PNG_S_MOD *pstMod, KG_CHAR scToken)
{
    PNG_S_NODE *pstItem = NULL;
    PNG_S_NODE *pstHead = NULL;
    PNG_S_DATA *pstData = NULL;
    
    KG_ASSERT_RET(NULL != pstMod, NULL);
    
    pstHead = &pstMod->stList;
    FOR_EACH_LIST_ITEM(pstItem, pstHead)
    {
        pstData = &pstItem->stData;
        if (scToken == pstData->scToken)
        {
            return pstItem;
        }
    }

    return NULL;
}

KG_S32 png_list_delete(PNG_S_MOD *pstMod, KG_CHAR scToken)
{
    PNG_S_NODE *pstItem = NULL;

    KG_ASSERT_RET(NULL != pstMod, KG_FAILURE);
    
    pstItem = png_list_search(pstMod, scToken);
    KG_ASSERT_RET(NULL != pstItem, KG_FAILURE);

    LIST_REMOVE(pstItem);
    SAFE_FREE(pstItem);

    return KG_SUCCESS;
}

KG_S32 png_list_init(PNG_S_MOD *pstMod)
{
    PNG_S_NODE *pstHead = NULL;
    
    KG_ASSERT_RET(NULL != pstMod, KG_FAILURE);

    memset(pstMod, 0, sizeof(PNG_S_MOD));
    pstHead = &pstMod->stList;
    LIST_INIT(pstHead);

    return KG_SUCCESS;
}

KG_S32 png_list_deinit(PNG_S_MOD *pstMod)
{
    PNG_S_NODE *pstItem = NULL;
    PNG_S_NODE *pstHead = NULL;
    PNG_S_DATA *pstData = NULL;
    KG_CHAR *pcRgbaBuf = NULL;

    KG_ASSERT_RET(NULL != pstMod, KG_FAILURE);
    
    pstHead = &pstMod->stList;
    FOR_EACH_LIST_ITEM(pstItem, pstHead)
    {
        pstData = &pstItem->stData;
        pcRgbaBuf = pstData->pscAddr;

        SAFE_FREE(pcRgbaBuf);
        LIST_REMOVE(pstItem);
        SAFE_FREE(pstItem);
        pstMod->u32Cnt--;
    }
    pstMod->u32Cnt = 0;

    return KG_SUCCESS;
}

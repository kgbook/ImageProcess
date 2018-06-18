#ifndef _PNG_LIST_H_
#define _PNG_LIST_H_

#include "png_splice.h"
#include "typedefs.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

KG_S32 png_list_query(PNG_S_MOD *pstMod);
KG_S32 png_list_insert(PNG_S_MOD *pstMod, PNG_S_DATA *pstData);
PNG_S_NODE *png_list_search(PNG_S_MOD *pstMod, KG_CHAR scToken);
KG_S32 png_list_delete(PNG_S_MOD *pstMod, KG_CHAR scToken);
KG_S32 png_list_init(PNG_S_MOD *pstMod);
KG_S32 png_list_deinit(PNG_S_MOD *pstMod);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

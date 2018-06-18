#ifndef __LIST_H__
#define __LIST_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define LIST_INIT(pstHead)  (pstHead)->next = (pstHead)->prev = (pstHead)
#define LIST_IS_EMPTY(pstHead) ((pstHead)->next == (pstHead))

//ptr point to a member of type, LIST_GET_ENTRY() return the entry of type
#define LIST_GET_ENTRY(ptr, type, member) ((type *)((type *)ptr - (unsigned long)(&((type *)0)->member)))

#define FOR_EACH_LIST_ITEM(pstItem, pstHead)  for(pstItem = (pstHead)->next; pstItem != pstHead; pstItem = (pstItem)->next)

#define FOR_EACH_LIST_ITEM_SAFE(pstItem, pstTemp, pstHead) \
    for( (pstItem) = (pstHead)->next, (pstTemp) = (pstItem)->next; \
        (pstItem) != (pstHead); \
            pstItem) = (pstTemp), (pstTemp) = (pstItem)->next )

#define FOR_EACH_LIST_ITEM_INVERT_SAFE(pstItem, pstTemp, pstHead) \
    for( (pstItem) = (pstHead)->prev, (pstTemp) = (pstItem)->prev; \
        (pstItem) != (pstHead); \
            (pstItem) = (pstTemp), (pstTemp) = (pstItem)->prev )

#define LIST_ADD_AFTER(pstItem, pstWhere) \
do \
{ \
    (pstItem)->next = (pstWhere)->next; \
    (pstItem)->prev = (pstWhere); \
    (pstWhere)->next = (pstItem); \
    (pstItem)->next->prev = (pstItem); \
}while(0)

#define LIST_ADD_BEFORE(pstItem, pstWhere)  LIST_ADD_AFTER(pstItem, (pstWhere)->prev)

#define LIST_REMOVE(pstItem)\
do \
{ \
    (pstItem)->prev->next = (pstItem)->next; \
    (pstItem)->next->prev = (pstItem)->prev; \
}while(0)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

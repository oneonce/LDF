/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: list_head.h
**功能描述: 双向链表(linux移植而来)
**作       者: oneonce
**日       期: 2020.03.27
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#ifndef __LIST_HEAD_H__
#define __LIST_HEAD_H__
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
    




typedef struct list_head
{
    struct list_head* next;
    struct list_head* prev;
} list_head_t;


#ifndef offsetof

#define offsetof(s,m)                       ((size_t)&(((s*)0)->m))

#endif

#ifndef container_of

#define container_of(ptr, type, member)     ((type *)((char *)ptr - offsetof(type, member)))

#endif



#define LIST_HEAD_INIT(name)                { &(name), &(name) }

#undef LIST_HEAD
#define LIST_HEAD(name)                     struct list_head name = LIST_HEAD_INIT(name)

/**********************************************************************************************************************
**函数名称: list_entry
**功能描述: 根据type(实际数据类型)、field(实际数据类型中list_head成员)得到指向实际数据类型的指针(ptr)
**输入参数:
**                type: 实际数据类型
**                field: 实际数据类型中list_head成员
**输出参数:
**                ptr: 输入参数, list_head*类型指针
**函数返回: 指向实际数据类型的指针对象
**********************************************************************************************************************/
#define list_entry(ptr, type, field)        container_of(ptr, type, field)

/**********************************************************************************************************************
**函数名称: list_first_entry
**功能描述: 根据type(实际数据类型)、field(实际数据类型中list_head成员)得到指向列表中第一个实际数据类型的指针(ptr)
**输入参数:
**                type: 实际数据类型
**                field: 实际数据类型中list_head成员
**输出参数:
**                ptr: 输入参数, list_head*类型指针
**函数返回: 指向第一个节点数据指针
**********************************************************************************************************************/
#define list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)

/**********************************************************************************************************************
**函数名称: list_first_entry
**功能描述: 根据type(实际数据类型)、field(实际数据类型中list_head成员)得到指向列表中最后一个实际数据类型的指针(ptr)
**输入参数:
**                type: 实际数据类型
**                field: 实际数据类型中list_head成员
**输出参数:
**                ptr: list_head*类型指针
**函数返回: 指向最后一个节点数据指针
**********************************************************************************************************************/
#define list_last_entry(ptr, type, field)   list_entry((ptr)->prev, type, field)

/**********************************************************************************************************************
**函数名称: list_for_each
**功能描述: 对链表for循环，每次迭代得到的list_head对象由ptr传出，使用list_entry(ptr)可得到指向实际数据对象的指针
**输入参数:
**                list: 链表表头
**输出参数:
**                ptr: list_head类型指针
**
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each(ptr, list)            for (ptr = (list)->next; ptr != (list); ptr = ptr->next)

/**********************************************************************************************************************
**函数名称: list_for_each_safe
**功能描述: 对链表for循环(安全版本)，每次迭代得到的list_head对象由ptr传出，使用list_entry(ptr)可得到指向实际数据对象的指针
**输入参数:
**                tmp: 临时变量
**                list: 链表表头
**输出参数:
**                ptr: list_head类型指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_safe(ptr, tmp, list)  for (ptr = (list)->next, tmp = ptr->next; ptr != (list); ptr = tmp, tmp = ptr->next)

/**********************************************************************************************************************
**函数名称: list_for_each_prev
**功能描述: 对链表从后向前for循环(安全版本)，每次迭代得到的list_head对象由ptr传出，使用list_entry(ptr)可得到指向实际数据
**                对象的指针
**输入参数:
**                list: 链表表头
**输出参数:
**                ptr: list_head类型指针
**
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_prev(ptr, list)       for (ptr = (list)->prev; ptr != (list); ptr = ptr->prev)

/**********************************************************************************************************************
**函数名称: list_for_each_prev_safe
**功能描述: 对链表从后向前for循环()，每次迭代得到的list_head对象由ptr传出，使用list_entry(ptr)可得到指向实际数据对象的指针
**输入参数:
**                tmp: 临时变量
**                list: 链表表头
**输出参数:
**                ptr: list_head类型指针
**
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_prev_safe(ptr, tmp, list) for (ptr = (list)->prev, tmp = ptr->prev; \
                                                ptr != (list); \
                                                ptr = tmp, tmp = ptr->prev)

/**********************************************************************************************************************
**函数名称: list_for_each_entry
**功能描述: 对链表for循环
**输入参数:
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 实际数据类型指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry(ptr, list, type, field) for (ptr = list_first_entry(list, type, field); \
                                                    &ptr->field != (list); \
                                                    ptr = list_entry(ptr->field.next, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_safe
**功能描述: 对给定的链表(h)进行for循环(安全版本)
**输入参数:
**                tmp: for内部临时变量
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_safe(ptr, tmp, list, type, field)   for (ptr = list_first_entry(list, type, field), \
                                                                tmp = list_entry(ptr->field.next, type, field); \
                                                                &ptr->field != (list); \
                                                                ptr = tmp, tmp = list_entry(ptr->field.next, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_reverse
**功能描述: 对给定的链表(h)进行反向for循环
**输入参数:
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_reverse(ptr, list, type, field)     for (ptr = list_last_entry(list, type, field); \
                                                                &ptr->field != (list); \
                                                                ptr = list_entry(ptr->field.prev, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_reverse_safe
**功能描述: 对链表反向for循环(安全版本)
**输入参数:
**                tmp: 临时变量
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_reverse_safe(ptr, tmp, list, type, field)   for (ptr = list_last_entry(list, type, field), \
                                                                        tmp = list_entry(ptr->field.prev, type, field); \
                                                                        &ptr->field != (list); \
                                                                        ptr = tmp, tmp = list_entry(ptr->field.prev, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_continue
**功能描述: 从给定节点(ptr)的下/后一个位置开始for循环
**输入参数:
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_continue(ptr, list, type, field)    for (ptr = list_entry(ptr->field.next, type, field); \
                                                                &ptr->field != (list); \
                                                                ptr = list_entry(ptr->field.next, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_continue_safe
**功能描述: 从给定节点(ptr)的下/后一个位置进行for循环(安全版本)
**输入参数:
**                tmp: 临时变量
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_continue_safe(ptr, tmp, list, type, field)  for (ptr = list_entry(ptr->field.next, type, field), \
                                                                        tmp = list_entry(ptr->field.next, type, field); \
                                                                        &ptr->field != (list); \
                                                                        ptr = tmp, tmp = list_entry(tmp->field.next, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_continue_reverse
**功能描述: 从给定节点(ptr)的上/前一个位置反向for循环
**输入参数:
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_continue_reverse(ptr, list, type, field)    for (ptr = list_entry(ptr->field.prev, type, field); \
                                                                        &ptr->field != (list); \
                                                                        ptr = list_entry(ptr->field.prev, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_continue_reverse
**功能描述: 从给定节点(ptr)的上/前一个位置反向for循环(安全版本)
**输入参数:
**                tmp: 传入参数，做为for内部临时变量
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_continue_reverse_safe(ptr, tmp, list, type, field)  for (ptr = list_entry(ptr->field.prev, type, field), \
                                                                                tmp = list_entry(ptr->field.prev, type, field); \
                                                                                &ptr->field != (list); \
                                                                                ptr = tmp, tmp = list_entry(tmp->field.prev, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_from
**功能描述: 从给定节点(ptr)的位置(包括给定节点)进行for循环
**输入参数:
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_from(ptr, list, type, field)    for (; &ptr->field != (list); \
                                                            ptr = list_entry(ptr->field.next, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_from_safe
**功能描述: 从给定节点(ptr)的位置(包括给定节点)for循环(安全版本)
**输入参数:
**                tmp: 做为for内部临时变量
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_from_safe(ptr, tmp, list, type, field)  for (tmp = list_entry(ptr->field.next, type, field); \
                                                                    &ptr->field != (list); \
                                                                    ptr = tmp, tmp = list_entry(tmp->field.next, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_from_reverse
**功能描述: 从给定节点(ptr)的位置(包括给定节点)反向for循环
**输入参数:
**                list: 待循环的链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_from_reverse(ptr, list, type, field)    for (; &ptr->field != (list); \
                                                                    ptr = list_entry(ptr->field.prev, type, field))

/**********************************************************************************************************************
**函数名称: list_for_each_entry_from_reverse_safe
**功能描述: 从给定节点(ptr)的位置(包括给定节点)反向for循环(安全版本)
**输入参数:
**                tmp: 传入参数，做为for内部临时变量
**                list: 链表表头
**                type: 实际数据类型
**                field: list_head在实际数据类型中的成员
**输出参数:
**                ptr: 指向实际数据类型的指针
**函数返回: 无
**********************************************************************************************************************/
#define list_for_each_entry_from_reverse_safe(ptr, tmp, list, type, field)  for (tmp = list_entry(ptr->field.prev, type, field); \
                                                                            &ptr->field != (list); \
                                                                            ptr = tmp, tmp = list_entry(tmp->field.prev, type, field))

/**********************************************************************************************************************
**函数名称: INIT_LIST_HEAD
**功能描述: 链表初始化
**输入参数:
**                list: 链表表头
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
static inline void INIT_LIST_HEAD(list_head_t* list)
{
    list->next = list->prev = list;
}

/**********************************************************************************************************************
**函数名称: list_empty
**功能描述: 检查链表是否为空(无节点)
**输入参数:
**                list: 链表表头
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
static inline bool list_empty(const list_head_t* list)
{
    return (list->next == list);
}

/**********************************************************************************************************************
**函数名称: list_is_first
**功能描述: 检查指定节点是否为链表第一个节点
**输入参数:
**                list: 链表表头
**                entry: 待检查的节点
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
static inline bool list_is_first(const list_head_t* list, const list_head_t* entry)
{
    return (entry->prev == list);
}

/**********************************************************************************************************************
**函数名称: list_is_last
**功能描述: 检查指定节点是否为链表最后一个节点
**输入参数:
**                list: 链表表头
**                entry: 待检查的节点
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
static inline bool list_is_last(const list_head_t* list, const list_head_t* entry)
{
    return (entry->next == list);
}

static inline void _list_del(list_head_t* entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

/**********************************************************************************************************************
**函数名称: list_delete
**功能描述: 把给定的节点entry从链表中删除
**                注意: 仅处理next和prev指针，并未释放内存
**输入参数:
**                entry: 待删除的节点
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
static inline void list_delete(list_head_t* entry)
{
    _list_del(entry);
    entry->next = entry->prev = NULL;
}

static inline void list_del_init(list_head_t* entry)
{
    _list_del(entry);
    INIT_LIST_HEAD(entry);
}

static inline void _list_add(list_head_t* entry, list_head_t* prev, list_head_t* next)
{
    next->prev = entry;
    entry->next = next;
    entry->prev = prev;
    prev->next = entry;
}

/**********************************************************************************************************************
**函数名称: list_add_head
**功能描述: 把给定的节点添加到链表表头
**输入参数:
**                list: 链表
**                entry: 待添加到链表中的节点
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
static inline void list_add_head(list_head_t* list, list_head_t* entry)
{
    _list_add(entry, list, list->next);
}

/**********************************************************************************************************************
**函数名称: list_add_tail
**功能描述: 把给定的节点添加到链表尾部
**输入参数:
**                list: 链表
**                entry: 待添加到链表中的节点
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
static inline void list_add_tail(list_head_t* list, list_head_t* entry)
{
    _list_add(entry, list->prev, list);
}

/**********************************************************************************************************************
**函数名称: list_move_head
**功能描述: 把指定的节点移动到表头
**输入参数:
**                list: 链表表头
**                entry: 待检查的节点
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
static inline void list_move_head(list_head_t* list, list_head_t* entry)
{
    _list_del(entry);
    list_add_head(list, entry);
}

/**********************************************************************************************************************
**函数名称: list_move_tail
**功能描述: 把指定的节点移动到表尾
**输入参数:
**                list: 链表表头
**                entry: 待检查的节点
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
static inline void list_move_tail(list_head_t* list, list_head_t* entry)
{
    _list_del(entry);
    list_add_tail(list, entry);
}


#ifdef __cplusplus
}
#endif

#endif // !__LIST_HEAD_H__

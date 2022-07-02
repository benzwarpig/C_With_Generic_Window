
#ifndef GENERICS_INTERFACE_H
#define GENERICS_INTERFACE_H

#include <stdbool.h>

#include "test_generics.h"
#include "generics_util.h"

/**
 * @file generics_interface.h
 * @author benzs_war_pig (benzwarpig@outlook.com)
 * @brief 该文件实现了一些操作泛型顺序表的算法，如排序，查找，遍历，判断变化率等等
 *
 *        this file implements some algorithms for operating generic sequential tables, such as sorting, searching, traversing,
 *          judging the rate of change, and so on
 *
 * @version 1.0
 * @date 2022-06-30
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @brief 对窗口进行冒泡排序
 *
 * @param tmp window
 */
static inline void ValueWindowBubbleSort( ValueWindowSquential* tmp )
{
    bool is_end_loop = true;

    for ( int i = 0; i < tmp->max_size && is_end_loop; i++ )
    {
        is_end_loop = false;
        for ( int j = tmp->max_size - 1; j >= i; j-- )
        {
            if ( ComparMemberValue( tmp, j - 1, j ) > 0 )
            {
                is_end_loop = true;
                SwapMemberValue( tmp, j - 1, j );
            }
        }
    }
}

/**
 * @brief 对窗口进行选择排序
 *
 * @param tmp window
 */
static inline void ValueWindowSelectSort( ValueWindowSquential* tmp )
{
    int min_index = 0;

    for ( int i = 0; i < tmp->max_size; i++ )
    {
        min_index = i;

        for ( int j = i; j < tmp->max_size; j++ )
        {
            if ( ComparMemberValue( tmp, min_index, j ) > 0 )
            {
                min_index = j;
            }
        }
        if ( i != min_index )
        {
            SwapMemberValue( tmp, i, min_index );
        }
    }
}

/**
 * @brief 对窗口进行直接插入排序
 *
 * @param tmp window
 */
static inline void ValueWindowInsertSort( ValueWindowSquential* tmp )
{
    void* tmp_value = ( void* ) malloc( tmp->type_size );
    int   j         = 0;

    for ( int i = 1; i < tmp->max_size; i++ )
    {
        if ( ComparMemberValue( tmp, i - 1, i ) > 0 )
        {
            GetMemberValue( tmp, tmp_value, i );

            for ( j = i - 1; ComparMemberValueFree( tmp, j, tmp_value ) && j >= 0; j-- )
            {
                SetMemberToMember( tmp, j + 1, j );
            }
            SetMemberValue( tmp, tmp_value, j + 1 );
        }
    }

    free( tmp_value );
}
#endif // generics_interface_H

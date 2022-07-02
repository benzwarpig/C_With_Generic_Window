#ifndef __GENERICS_UTIL_H
#define __GENERICS_UTIL_H

#include "test_generics.h"

/*
    1. 实现 buffer[i] = res; 设置任意成员的值
    2. 实现 res = buffer[i]; 获取任意成员的值
    3. 实现 buffer[i] = buffer[j]; 将任意成员的值赋值给任意成员
    4. 实现 buffer[i] <=> buffer[j] ; 实现任意成员比大小
    5. 实现 swap(i,j); 交换任意两个成员值
*/

// 工具函数 获取窗口任意下标对应的地址 不对外暴露
static inline void* GetMemberAddress( ValueWindowSquential* tmp, int i )
{
    return ( void* ) ( tmp->data + i * tmp->type_size );
}

// 打印任意类型数据的十六进制编码 调试用
static inline void ShowTypeChangeToHex( ValueWindowSquential* tmp, int i )
{
    uint8_t* res = ( uint8_t* ) GetMemberAddress( tmp, i );
    for ( int i = 0; i < tmp->type_size; i++ )
    {
        printf( "Hex : 0x%x \r\n", *res++ );
    }
}

// 1. 设置任意成员的值
static inline void SetMemberValue( ValueWindowSquential* tmp, void* value, int i )
{
    memcpy( GetMemberAddress( tmp, i ), value, tmp->type_size );
}

// 2. 获取任意成员的值
static inline void GetMemberValue( ValueWindowSquential* tmp, void* value, int i )
{
    memcpy( value, GetMemberAddress( tmp, i ), tmp->type_size );
}

// 3. 将任意成员的值赋值给任意成员
static inline void SetMemberToMember( ValueWindowSquential* tmp, int i, int j )
{
    memcpy( GetMemberAddress( tmp, i ), GetMemberAddress( tmp, j ), tmp->type_size );
}

// 4. 对比两个成员大小，顺序为 i > = < j
static inline int ComparMemberValue( ValueWindowSquential* tmp, int i, int j )
{
    int res = 0;

    uint8_t* value_i = ( uint8_t* ) GetMemberAddress( tmp, i );
    uint8_t* value_j = ( uint8_t* ) GetMemberAddress( tmp, j );

    for ( int k = tmp->type_size - 1; k >= 0; k-- )
    {
        res = memcmp( value_i + k, value_j + k, sizeof( uint8_t ) );
        if ( res != 0 )
        {
            break;
        }
    }
    return res;
}

// 4. 对比任意成员与任意值的大小,服务于插入排序
static inline int ComparMemberValueFree( ValueWindowSquential* tmp, int i, void* j )
{
    int res = 0;

    uint8_t* value_i = ( uint8_t* ) GetMemberAddress( tmp, i );
    uint8_t* value_j = ( uint8_t* ) j;

    for ( int k = tmp->type_size - 1; k >= 0; k-- )
    {
        res = memcmp( value_i + k, value_j + k, sizeof( uint8_t ) );
        if ( res != 0 )
        {
            break;
        }
    }
    return res;
}

// 5. 交换任意两个成员值
static inline void SwapMemberValue( ValueWindowSquential* tmp, int i, int j )
{
    void* tmp_value = ( void* ) malloc( tmp->type_size );

    GetMemberValue( tmp, tmp_value, i );
    SetMemberToMember( tmp, i, j );
    SetMemberValue( tmp, tmp_value, j );

    free( tmp_value );
}

#endif // __GENERICS_UTIL_H
/**
 * @file test_generics.cpp
 * @author benzs_war_pig (benzwarpig@outlook.com)
 * @brief   构建一种基于C的泛型顺序表,针对不同类型的顺序表，实现接口一致化。
 *        同时针对顺序表实现一些常用操作（排序，滤波，统计等）
 *
 *          build a generic sequence table based on C, and realize interface consistency
 *          for different types of sequence tables. At the same time, some common operations (sorting, filtering, statistics, etc.)
 *          are implemented for the sequence table
 *
 * @version 1.0
 * @date 2022-06-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "test_generics.h"

#include "generics_interface.h"
#include "generics_util.h"

/**
 * @brief 将字符串转换成TypeName
 *          private interface
 *
 * @param tmp
 * @return TypeName
 */
TypeName ChangeStringToEnum( const char* tmp )
{
    assert( tmp != NULL );

    TypeName return_tmp = ERROR;

    if ( strcmp( tmp, kValueTypeList[ UINT8 ] ) == 0 )
    {
        return_tmp = UINT8;
    }
    else if ( strcmp( tmp, kValueTypeList[ FLOAT ] ) == 0 )
    {
        return_tmp = FLOAT;
    }
    else if ( strcmp( tmp, kValueTypeList[ DOUBLE ] ) == 0 )
    {
        return_tmp = DOUBLE;
    }
    else if ( strcmp( tmp, kValueTypeList[ INT ] ) == 0 )
    {
        return_tmp = INT;
    }
    else
    {
        printf( "error char* input !!!" );
        assert( 0 );
    }
    return return_tmp;
}

// 初始化窗口
// Initialize window
void InitValueWindow( ValueWindowSquential* tmp, const char* type, uint32_t max_size )
{
    assert( tmp != NULL );

    tmp->type = ( char* ) malloc( strlen( type ) * sizeof( char ) );
    strncpy( tmp->type, type, strlen( type ) );

    tmp->max_size = max_size;
    tmp->sequence = 0;

    switch ( ChangeStringToEnum( tmp->type ) )
    {
        case UINT8: {
            tmp->data = ( uint8_t* ) malloc( max_size * sizeof( uint8_t ) );
            memset( tmp->data, 0, tmp->max_size );

            tmp->type_size = sizeof( uint8_t );
        }
        break;

        case INT: {
            tmp->data = ( int* ) malloc( max_size * sizeof( int ) );
            memset( tmp->data, 0, tmp->max_size );

            tmp->type_size = sizeof( int );
        }
        break;

        case FLOAT: {
            tmp->data = ( float* ) malloc( max_size * sizeof( float ) );
            memset( tmp->data, 0, tmp->max_size );

            tmp->type_size = sizeof( float );
        }
        break;

        case DOUBLE: {
            tmp->data = ( double* ) malloc( max_size * sizeof( double ) );
            memset( tmp->data, 0, tmp->max_size );

            tmp->type_size = sizeof( double );
        }
        break;

        default: {
            printf( "error tmp->type input !!!" );
            assert( 0 );
        }
        break;
    }

    printf( "type is : %s , max_size is : %d , type_size is : %d \r\n",
            tmp->type, max_size, tmp->type_size );
}

// 重置/销毁窗口
void ResetValueWindow( ValueWindowSquential* tmp )
{
    tmp->sequence  = 0;
    tmp->max_size  = 0;
    tmp->type_size = 0;

    if ( tmp->data != NULL )
    {
        free( tmp->data );
        tmp->data = NULL;
    }

    if ( tmp->type != NULL )
    {
        free( tmp->type );
        tmp->type = NULL;
    }
}

// 滑动往窗口插入数据
SlideWindowState ValueWindowSlideInsert( ValueWindowSquential* tmp, void* data )
{
    SlideWindowState return_tmp = kWindowIsNotFull;

    for ( int i = 1; i < tmp->max_size; i++ )
    {
        SetMemberToMember( tmp, i - 1, i );
    }
    SetMemberValue( tmp, data, tmp->max_size - 1 );

    // just for return window state
    if ( ++tmp->sequence >= tmp->max_size )
    {
        return_tmp    = kWindowIsSliding;
        tmp->sequence = tmp->max_size;
    }

    return return_tmp;
}

// 插入数据直到填满整个窗口
FixedWindowState ValueWindowFixedInsert( ValueWindowSquential* tmp, void* data )
{
    FixedWindowState return_tmp = kWindowNotFull;

    SetMemberValue( tmp, data, tmp->sequence );

    if ( ++tmp->sequence >= tmp->max_size )
    {
        tmp->sequence = 0;
        return_tmp    = kWindowAlreadyFull;
    }
    return return_tmp;
}

// 打印窗口内全部值
void ShowTheWindow( ValueWindowSquential* tmp )
{
    // printf("current_type:{%d}", ChangeStringToEnum(tmp->type));
    switch ( ChangeStringToEnum( tmp->type ) )
    {
        case UINT8: {
            uint8_t* msg = ( uint8_t* ) tmp->data;
            for ( int i = 0; i < tmp->max_size; ++i )
            {
                printf( "i : {%d} , %d \r\n", i, msg[ i ] );
            }
        }
        break;

        case INT: {
            int* msg = ( int* ) tmp->data;
            for ( int i = 0; i < tmp->max_size; ++i )
            {
                printf( "i : {%d} , %d \r\n", i, msg[ i ] );
            }
        }
        break;

        case FLOAT: {
            float* msg = ( float* ) tmp->data;
            for ( int i = 0; i < tmp->max_size; ++i )
            {
                printf( "i : {%d} , %f \r\n", i, msg[ i ] );
            }
        }
        break;

        case DOUBLE: {
            double* msg = ( double* ) tmp->data;
            for ( int i = 0; i < tmp->max_size; ++i )
            {
                printf( "i : {%d} , %f \r\n", i, msg[ i ] );
            }
        }
        break;

        default: {
            printf( "error tmp->type input !!!" );
            assert( 0 );
        }
        break;
    }
}

int main( void )
{
    // 1. 创建一个泛型窗口，并以float类型，10个窗口大小初始化
    ValueWindowSquential tmp;
    InitValueWindow( &tmp, kValueTypeList[ FLOAT ], 10 );

    float insert_data = 0;
    for ( int i = 0; i < tmp.max_size; i++ )
    {
        // 2. 插入数据到窗口中，直到接收到窗口满反馈
        insert_data = ( tmp.max_size - i ) * 1.1;
        if ( kWindowAlreadyFull == ValueWindowFixedInsert( &tmp, &insert_data ) )
        {
            // 3. 打印排序前窗口
            printf( "start sort \r\n" );
            ShowTheWindow( &tmp );

            // 4. 通过直接插入排序法对窗口进行排序
            ValueWindowInsertSort( &tmp );

            // 5. 打印排序后的窗口
            printf( "end sort \r\n" );
            ShowTheWindow( &tmp );

            break;
        }
    }
    ResetValueWindow( &tmp );

    printf( "test generics \r\n" );
    return 0;
}
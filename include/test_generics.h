#ifndef __TEST_GENERICS_h
#define __TEST_GENERICS_h

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include <assert.h>

typedef signed char   int8_t;
typedef unsigned char uint8_t;

typedef signed short   int16_t;
typedef unsigned short uint16_t;

typedef signed int   int32_t;
typedef unsigned int uint32_t;

typedef enum
{
    UINT8 = 0,
    INT,
    FLOAT,
    DOUBLE,

    ERROR

} TypeName;

const char* kValueTypeList[ ERROR + 1 ] = {

    "uint8_t",

    "int",
    "float",
    "double",

    "error",
};

TypeName ChangeStringToEnum( const char* tmp );

/**
 * @brief 该结构体用于构建基础窗口顺序表
 *        this structure is used to build the basic window sequence table
 */
typedef struct ValueWindowSquential
{
    char* type;
    void* data;

    uint16_t type_size;

    uint32_t max_size;

    uint32_t sequence;

} ValueWindowSquential;

/**
 * @brief 初始化窗口，根据窗口类型，大小，动态分配内存给到内部缓冲区
 *        initialize the window, and dynamically allocate memory to the internal buffer according to the window type and size
 *
 * @param tmp base structure for Window
 * @param type Window type
 * @param max_size Window size
 *
 * @throw assert
 */
void InitValueWindow( ValueWindowSquential* tmp, const char* type, uint32_t max_size );

/**
 * @brief 重置或销毁窗口
 *        reset or destroy window
 *
 * @param tmp base structure for Window
 */
void ResetValueWindow( ValueWindowSquential* tmp );

typedef enum
{
    kWindowIsNotFull = ( 0 ),
    kWindowIsSliding,

    kWindowCanNotInsert,
    kWindowInputFail,

} SlideWindowState;
/**
 * @brief 滑动插入数据进入窗口，先入先出（FIFO模型）
 *        slide insert data into the window, first in first out (FIFO model)
 *
 * @param tmp base structure for Window
 * @param data insert data
 *
 * @return SlideWindowState
 *              kWindowIsNotFull    窗口未填充满
 *              kWindowIsSliding    窗口已填充满并开始滑动
 *
 *              kWindowCanNotInsert 窗口不允许插入
 *              kWindowInputFail    窗口插入数据失败
 */
SlideWindowState ValueWindowSlideInsert( ValueWindowSquential* tmp, void* data );

typedef enum
{
    kWindowNotFull = ( 0 ),
    kWindowAlreadyFull,

    kFixWindowCanNotInsert,
    kFixWindowInputFail,

} FixedWindowState;
/**
 * @brief 固定窗，往窗口里插入数据，直到窗口满了反馈 kWindowAlreadyFull ，否在反馈 kWindowNotFull
 *        与滑动窗区别是，固定窗会采集多组数据，采集完成才能使用窗口，使用完后从头重新采集
 *        也就是降频处理数据，窗口大小20,10ms插入一次，那么降频到200ms处理一次窗口（数据）
 *
 * @param tmp base structure for Window
 * @param data insert data
 *
 * @return FixedWindowState
 *              kWindowNotFull 窗口未满
 *              kWindowAlreadyFull 窗口已满，可以开始操作
 *
 *              kFixWindowCanNotInsert 窗口不允许插入
 *              kFixWindowInputFail 窗口插入数据失败
 */
FixedWindowState ValueWindowFixedInsert( ValueWindowSquential* tmp, void* data );

/**
 * @brief 遍历并打印窗口
 *
 * @param tmp base structure for Window
 */
void ShowTheWindow( ValueWindowSquential* tmp );

#endif // __TEST_GENERICS_h

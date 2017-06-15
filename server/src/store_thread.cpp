#include "header/store_thread.h"

/**************************************************
*作者：Liu Chaoyang
*日期：2017.06.12
*函数名：StoreThread
*功能：Constructor of StoreThread
*输入参数：log_dao
*输出参数：none
*返回值：none
**************************************************/

StoreThread::StoreThread(FileDao &file_dao, OracleDao &oracle_dao)
    : file_dao(file_dao),
      oracle_dao(oracle_dao)
{

}

/**************************************************
*作者：Liu Chaoyang
*日期：2017.06.12
*函数名：~StoreThread
*功能：Destructor of StoreThread
*输入参数：none
*输出参数：none
*返回值：none
**************************************************/

StoreThread::~StoreThread()
{

}

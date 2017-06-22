#include "header/log_queue.h"
#include <iostream>
#include "header/server_exception.h"
#define __DEBUG__

using std::list;
using std::cout;
using std::endl;

LogQueue::LogQueue()
{

    int res;
    res = pthread_mutex_init(&client_store_mutex, NULL);
    if (res != 0)
    {
#ifdef __DEBUG__
        cout << "Thread mutex initialization failed!" << endl;
#endif
        throw ServerException("Thread mutex initialization failed!");
    }
    else
    {
#ifdef __DEBUG__
        cout << "Thread mutex initialization succeeded." << endl;
#endif
    }
    res = pthread_cond_init(&not_full, NULL);
    if (res != 0)
    {
#ifdef __DEBUG__
        cout << "Thread condition: 'not_full' initialization failed!" << endl;
#endif
        throw ServerException("Thread condition: 'not_full' initialization failed!");
    }
    else
    {
#ifdef __DEBUG__
        cout << "Thread condition: 'not_full' initialization succeeded." << endl;
#endif
    }
    res = pthread_cond_init(&not_empty, NULL);
    if (res != 0)
    {
#ifdef __DEBUG__
        cout << "Thread condition: 'not_empty' initialization failed!" << endl;
#endif
        throw ServerException("Thread condition: 'not_empty' initialization failed!");
    }
    else
    {
#ifdef __DEBUG__
        cout << "Thread condition: 'not_empty' initialization succeeded." << endl;
#endif
    }
}

//int LogQueue::getMaxSize()
//{
//    return max_size;
//}

//int LogQueue::getCurSize()
//{
//    return cur_size;
//}

LogQueue& LogQueue::operator <<(MatchedLogRec const& matched_log)
{
    pthread_mutex_lock(&client_store_mutex);
    if (log_record.size() == log_record.max_size())
    {
#ifdef __DEBUG__
        cout << "log Queue is full! Waiting for not-full ..." << endl;
#endif
        pthread_cond_wait(&not_full, &client_store_mutex);
    }
    log_record.push_back(matched_log);
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&client_store_mutex);
    return *this;
}

LogQueue& LogQueue::operator >>(MatchedLogRec& matched_log)
{
    pthread_mutex_lock(&client_store_mutex);
    if (log_record.size() == 0)
    {
#ifdef __DEBUG__
        cout << "log Queue is empty! Waiting for not-empty ..." << endl;
#endif
        pthread_cond_wait(&not_empty, &client_store_mutex);
    }
    matched_log = log_record.front();
    log_record.pop_front();
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&client_store_mutex);
    return *this;
}

LogQueue::~LogQueue()
{
    pthread_mutex_destroy(&client_store_mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
}

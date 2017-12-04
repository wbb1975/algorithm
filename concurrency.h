#ifndef CONCURRENCY_H_
#define CONCURRENCY_H_

#include <pthread.h>
#include <list>
#include <time.h>

namespace wangbb
{
    template <typename T>
    class Queue 
    {
    public: 
        Queue()
        { 
            pthread_mutex_init(&_lock, NULL);
            pthread_cond_init(&_cond,  NULL);
        } 
        ~Queue()
        { 
            pthread_mutex_destroy(&_lock);
            pthread_cond_destroy(&_cond);
        }
        
        void push(const T& data)
        {
            pthread_mutex_lock(&_lock);
            bool was_empty = _list.empty( );
            _list.push_back(data);
            pthread_mutex_unlock(&_lock);
            if (was_empty) 
               pthread_cond_broadcast(&_cond);
        }
        
        void push(const T& data, int seconds)
        {
            struct timespec ts1, ts2;
            const bool was_empty = _list.empty( );
            clock_gettime(CLOCK_REALTIME, &ts1);
            pthread_mutex_lock(&_lock);
            clock_gettime(CLOCK_REALTIME, &ts2);
            if ((ts2.tv_sec - ts1.tv_sec) < seconds)
            {
                was_empty = _list.empty( );
                _list.push_back(data);
            }
            pthread_mutex_unlock(&_lock);
            if (was_empty) 
                pthread_cond_broadcast(&_cond);
        }
        
        T pop( )
        {
            pthread_mutex_lock(&_lock);
            while(_list.empty( ))
            {
                pthread_cond_wait(&_cond, &_lock);
            }
            T _temp = _list.front( );
            _list.pop_front( );
            pthread_mutex_unlock(&_lock);
            return _temp;
        }
        
        T pop(int seconds)
        { 
            struct timespec ts1, ts2;
            int    result = 0;
            clock_gettime(CLOCK_REALTIME, &ts1); 
            pthread_mutex_lock(&_lock);
            clock_gettime(CLOCK_REALTIME, &ts2);

            // First Check
            if ((ts2.tv_sec - ts1.tv_sec) < seconds)
            {
                ts2.tv_sec += seconds;          // specify wake up time
                while(_list.empty( ) && (result == 0))
                {
                    result = pthread_cond_timedwait(&_cond, &_lock, &ts2);
                }
                if (result == 0)    // Second Check
                {
                    T _temp = _list.front( );
                    _list.pop_front( );
                    pthread_mutex_unlock(&_lock);
                    return _temp;
                }
            }
            pthread_mutex_unlock(&_lock);
            throw "timeout happend";
        }

    private: 
        std::list<T> _list; 
        pthread_mutex_t  _lock;
        pthread_cond_t   _cond;
    };
} // end of namespace 

#endif

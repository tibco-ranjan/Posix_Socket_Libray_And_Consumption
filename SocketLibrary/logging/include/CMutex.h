#ifndef CMUTEX_H
#define CMUTEX_H
#include <pthread.h>

/**
 * @brief: Mutex class to achieve synchronization 
 * 				
 */
class CMutex
{
    pthread_mutex_t  m_mutex;
 
  public:
    // just initialize to defaults
    CMutex() { pthread_mutex_init(&m_mutex, NULL); }
    virtual ~CMutex() { 
	    pthread_mutex_unlock(&m_mutex); 
	    pthread_mutex_destroy(&m_mutex); 
	}
 
    int lock() { return  pthread_mutex_lock(&m_mutex); }
    int trylock() { return  pthread_mutex_trylock(&m_mutex); }
    int unlock() { return  pthread_mutex_unlock(&m_mutex); }   
};
#endif /*CMUTEX_H*/


#include "ft_attr.h"


/*****************************************/
/*      attribute object routines        */
/*****************************************/



void forthread_attr_destroy(int *attr, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));

  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_destroy(((pthread_attr_t*)(thread_attrs->data[*attr])));

  if (*info) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    return;
  }
  free(thread_attrs->data[*attr]);
  thread_attrs->data[*attr] = NULL;

  pthread_mutex_unlock(&(thread_attrs->mutex));

}


void forthread_attr_init(int *attr, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));

  if (thread_attrs->after == thread_attrs->size) {
    // we exhausted the thread id and attribute arrays, double space
    array_resize(&thread_attrs,thread_attrs->size*2);
  }
  thread_attrs->data[thread_attrs->after] = 
    (pthread_attr_t*) malloc(sizeof(pthread_attr_t));

  *info = pthread_attr_init(thread_attrs->data[thread_attrs->after]);

  if (*info) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    return;
  }

  *attr = thread_attrs->after;
  thread_attrs->after++;

  pthread_mutex_unlock(&thread_attrs->mutex);

}

void forthread_attr_getdetachstate(int *attr, int *detachstate, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_getdetachstate((pthread_attr_t*)(thread_attrs->data[*attr]),detachstate);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_setdetachstate(int *attr, int *detachstate, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_setdetachstate((pthread_attr_t*)(thread_attrs->data[*attr]),*detachstate);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_getguardsize(int *attr, int *guardsize, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_getguardsize((pthread_attr_t*)(thread_attrs->data[*attr]),(size_t*)guardsize);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_setguardsize(int *attr, int *guardsize, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_setguardsize((pthread_attr_t*)(thread_attrs->data[*attr]),(size_t)*guardsize);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_getinheritsched(int *attr, int *inheritsched, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_getinheritsched((pthread_attr_t*)(thread_attrs->data[*attr]),inheritsched);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_setinheritsched(int *attr, int *inheritsched, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_setinheritsched((pthread_attr_t*)(thread_attrs->data[*attr]),*inheritsched);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

// implements pthreads getschedparam
void forthread_attr_getschedpriority(int *attr, int *sched_priority, int *info) {
  *info = FT_OK;
  struct sched_param param;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_getschedparam((pthread_attr_t*)(thread_attrs->data[*attr]),&param);

  *sched_priority = param.sched_priority;

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

// implements pthreads setschedparam
void forthread_attr_setschedpriority(int *attr, int *sched_priority, int *info) {
  *info = FT_OK;
  struct sched_param param;
  param.sched_priority = *sched_priority;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_setschedparam((pthread_attr_t*)(thread_attrs->data[*attr]),&param);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_getschedpolicy(int *attr, int *policy, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_getschedpolicy((pthread_attr_t*)(thread_attrs->data[*attr]),policy);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_setschedpolicy(int *attr, int *policy, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_setschedpolicy((pthread_attr_t*)(thread_attrs->data[*attr]),*policy);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_getscope(int *attr, int *scope, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_getscope((pthread_attr_t*)(thread_attrs->data[*attr]),scope);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_setscope(int *attr, int *scope, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_setscope((pthread_attr_t*)(thread_attrs->data[*attr]),*scope);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_getstacksize(int *attr, int *stacksize, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_getstacksize((pthread_attr_t*)(thread_attrs->data[*attr]),(size_t*)stacksize);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}

void forthread_attr_setstacksize(int *attr, int *stacksize, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(thread_attrs->mutex));
  if (!is_valid(thread_attrs,*attr)) {
    pthread_mutex_unlock(&(thread_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_attr_setstacksize((pthread_attr_t*)(thread_attrs->data[*attr]),(size_t)*stacksize);

  pthread_mutex_unlock(&(thread_attrs->mutex));

}


/*****************************************/
/*       mutex attribute routines        */
/*****************************************/

void forthread_mutexattr_destroy(int *attr,int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));

  if (!is_valid(mutex_attrs,*attr)) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_mutexattr_destroy(((pthread_mutexattr_t*)(
          mutex_attrs->data[*attr])));

  if (*info) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    return;
  }

  free(mutex_attrs->data[*attr]);
  mutex_attrs->data[*attr] = NULL;

  pthread_mutex_unlock(&(mutex_attrs->mutex));



}


void forthread_mutexattr_init(int *attr,int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));

  if (mutex_attrs->after == mutex_attrs->size) {
    // we exhausted the mutex attribute array, double space
    array_resize(&mutex_attrs,mutex_attrs->size*2);
  }
  mutex_attrs->data[mutex_attrs->after] = 
    (pthread_mutexattr_t*) malloc(sizeof(pthread_mutexattr_t));

  *info = pthread_mutexattr_init(mutex_attrs->data[mutex_attrs->after]);

  if (*info) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    return;
  }

  *attr = mutex_attrs->after;
  mutex_attrs->after++;

  pthread_mutex_unlock(&(mutex_attrs->mutex));

}

void forthread_mutexattr_getpshared(int *attr, int *pshared, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));
  if (!is_valid(mutex_attrs,*attr)) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_mutexattr_getpshared(
                 (pthread_mutexattr_t*)(mutex_attrs->data[*attr]),
                 pshared);

  pthread_mutex_unlock(&(mutex_attrs->mutex));

}

void forthread_mutexattr_setpshared(int *attr, int *pshared, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));
  if (!is_valid(mutex_attrs,*attr)) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_mutexattr_setpshared(
                 (pthread_mutexattr_t*)(mutex_attrs->data[*attr]),
                 *pshared);

  pthread_mutex_unlock(&(mutex_attrs->mutex));

}

void forthread_mutexattr_getprioceiling(int *attr, int *prioceiling, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));
  if (!is_valid(mutex_attrs,*attr)) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_mutexattr_getprioceiling(
                 (pthread_mutexattr_t*)(mutex_attrs->data[*attr]),
                 prioceiling);

  pthread_mutex_unlock(&(mutex_attrs->mutex));

}

void forthread_mutexattr_setprioceiling(int *attr, int *prioceiling, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));
  if (!is_valid(mutex_attrs,*attr)) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_mutexattr_setprioceiling(
                 (pthread_mutexattr_t*)(mutex_attrs->data[*attr]),
                 *prioceiling);

  pthread_mutex_unlock(&(mutex_attrs->mutex));

}

void forthread_mutexattr_getprotocol(int *attr, int *protocol, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));
  if (!is_valid(mutex_attrs,*attr)) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_mutexattr_getprotocol(
                 (pthread_mutexattr_t*)(mutex_attrs->data[*attr]),
                 protocol);

  pthread_mutex_unlock(&(mutex_attrs->mutex));

}

void forthread_mutexattr_setprotocol(int *attr, int *protocol, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));
  if (!is_valid(mutex_attrs,*attr)) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_mutexattr_setprotocol(
                 (pthread_mutexattr_t*)(mutex_attrs->data[*attr]),
                 *protocol);

  pthread_mutex_unlock(&(mutex_attrs->mutex));

}

void forthread_mutexattr_gettype(int *attr, int *type, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));
  if (!is_valid(mutex_attrs,*attr)) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_mutexattr_gettype(
                 (pthread_mutexattr_t*)(mutex_attrs->data[*attr]),
                 type);

  pthread_mutex_unlock(&(mutex_attrs->mutex));

}

void forthread_mutexattr_settype(int *attr, int *type, int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(mutex_attrs->mutex));
  if (!is_valid(mutex_attrs,*attr)) {
    pthread_mutex_unlock(&(mutex_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_mutexattr_settype(
                 (pthread_mutexattr_t*)(mutex_attrs->data[*attr]),
                 *type);

  pthread_mutex_unlock(&(mutex_attrs->mutex));

}

/*****************************************************/
/*    condition attriubute variable routines         */
/*****************************************************/


void forthread_condattr_destroy(int *attr,int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(cond_attrs->mutex));

  if (!is_valid(cond_attrs,*attr)) {
    pthread_mutex_unlock(&(cond_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_condattr_destroy(((pthread_condattr_t*)(
          cond_attrs->data[*attr])));

  if (*info) {
    pthread_mutex_unlock(&(cond_attrs->mutex));
    return;
  }

  free(cond_attrs->data[*attr]);
  cond_attrs->data[*attr] = NULL;

  pthread_mutex_unlock(&(cond_attrs->mutex));

}


void forthread_condattr_init(int *attr,int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(cond_attrs->mutex));

  if (cond_attrs->after == cond_attrs->size) {
    // we exhausted the mutex attribute array, double space
    array_resize(&cond_attrs,cond_attrs->size*2);
  }
  cond_attrs->data[cond_attrs->after] = 
    (pthread_condattr_t*) malloc(sizeof(pthread_condattr_t));

  *info = pthread_condattr_init(cond_attrs->data[cond_attrs->after]);

  if (*info) {
    pthread_mutex_unlock(&(cond_attrs->mutex));
    return;
  }

  *attr = cond_attrs->after;
  cond_attrs->after++;

  pthread_mutex_unlock(&(cond_attrs->mutex));

}


/**************************************************/
/*    barrier attribute variable routines         */
/**************************************************/


void forthread_barrierattr_destroy(int *attr,int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(barrier_attrs->mutex));

  if (!is_valid(barrier_attrs,*attr)) {
    pthread_mutex_unlock(&(barrier_attrs->mutex));
    *info = FT_EINVALID;
    return;
  }

  *info = pthread_barrierattr_destroy(((pthread_barrierattr_t*)(
          barrier_attrs->data[*attr])));

  if (*info) {
    pthread_mutex_unlock(&(barrier_attrs->mutex));
    return;
  }

  free(barrier_attrs->data[*attr]);
  barrier_attrs->data[*attr] = NULL;

  pthread_mutex_unlock(&(barrier_attrs->mutex));

}


void forthread_barrierattr_init(int *attr,int *info) {
  *info = FT_OK;

  if (!is_initialized) {
    *info = FT_EINIT;
    return;
  }

  pthread_mutex_lock(&(barrier_attrs->mutex));

  if (barrier_attrs->after == barrier_attrs->size) {
    // we exhausted the mutex attribute array, double space
    array_resize(&barrier_attrs,barrier_attrs->size*2);
  }
  barrier_attrs->data[barrier_attrs->after] = 
    (pthread_barrierattr_t*) malloc(sizeof(pthread_barrierattr_t));

  *info = pthread_barrierattr_init(barrier_attrs->data[barrier_attrs->after]);

  if (*info) {
    pthread_mutex_unlock(&(barrier_attrs->mutex));
    return;
  }

  *attr = barrier_attrs->after;
  barrier_attrs->after++;

  pthread_mutex_unlock(&(barrier_attrs->mutex));

}

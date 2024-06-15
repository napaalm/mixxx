#ifdef __LINUX__
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
// TODO: remove unused includes
#include <QFile>
#endif

#include <QThread>
#include <QtDebug>

#include "util/threadpriority.h"

#if __GLIBC__ == 2 && __GLIBC_MINOR__ < 30
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#endif

namespace mixxx {

bool ThreadPriority::setRealtimePriority(int priority) {
#ifdef __LINUX__
    qDebug() << "Set thread priority for Thread ID" << gettid();

    // Set scheduling policy and priority for the pthread
    struct sched_param params;
    params.sched_priority = priority;  // Set the priority value (0-99), where 99 is the highest priority

    if (pthread_setschedparam(pthread_self(), SCHED_RR, &params) != 0) {
        qDebug() << "Failed to set scheduling parameters for the thread.";
        return 1;
    }

    // Verify the scheduling policy and priority after setting
    int policy;
    pthread_getschedparam(pthread_self(), &policy, &params);
    qDebug() << "Thread scheduling policy: " << (policy == SCHED_RR ? "SCHED_RR" : "Unknown");
    qDebug() << "Thread priority: " << params.sched_priority;

    return true;
#else
    qWarning() << "Real-time thread priority not implemented on this platform";
    return false;
#endif
}

} // namespace mixxx

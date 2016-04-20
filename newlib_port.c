#include <esp_common.h>

int _getpid_r(struct _reent *ptr) {
    return 1;
}

int _kill_r(struct _reent *ptr, int pid, int sig) {
    ptr->_errno = EINVAL;
    return (-1);
}

int _raise_r(struct _reent *ptr, int sig) 
{
    ptr->_errno = EINVAL;
    return -1;
}

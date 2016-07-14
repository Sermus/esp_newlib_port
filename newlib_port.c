#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

#include <ets_sys.h>
#include <osapi.h>
#include <mem.h>
//#include <espmissingincludes.h>
#include <user_interface.h>

int errno;
int _write_r(struct _reent *ptr, int file, char *c, int len);

void _exit(int status) {
    _write_r(0, 1, "exit", 4);
    while (1) {
        ;
    }
}

int _close_r(struct _reent *ptr, int file) {
    ptr->_errno = EBADF;
    return -1;
}
int _open_r(struct _reent *ptr, int file, char *c, int flags, int mode) {
    ptr->_errno = EBADF;
    return -1;
}
/*
 execve
 Transfer control to a new process. Minimal implementation (for a system without processes):
 */
int _execve(char *name, char **argv, char **env) {
    errno = ENOMEM;
    return -1;
}
/*
 fork
 Create a new process. Minimal implementation (for a system without processes):
 */

int _fork() {
    errno = EAGAIN;
    return -1;
}
/*
 fstat
 Status of an open file. For consistency with other minimal implementations in these examples,
 all files are regarded as character special devices.
 The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.
 */
int _fstat_r(struct _reent *ptr, int file, struct stat *st) {
    switch (file){
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
        st->st_mode = S_IFCHR;
        return 0;
    default:
        ptr->_errno = EBADF;
        return -1;
    }
}

/*
 getpid
 Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes. Minimal implementation, for a system without processes:
 */

int _getpid_r(struct _reent *ptr) {
    return 1;
}

/*
 isatty
 Query whether output stream is a terminal. For consistency with the other minimal implementations,
 */
int _isatty(int file) {
    switch (file){
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
        return 1;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        return 0;
    }
}


/*
 kill
 Send a signal. Minimal implementation:
 */
int _kill_r(struct _reent *ptr, int pid, int sig) {
    ptr->_errno = EINVAL;
    return (-1);
}

/*
 link
 Establish a new name for an existing file. Minimal implementation:
 */

int _link(char *old, char *new) {
    errno = EMLINK;
    return -1;
}

/*
 lseek
 Set position in a file. Minimal implementation:
 */
int _lseek_r(struct _reent *ptr, int file, int pos, int dir) {
    ptr->_errno = EBADF;
    return 0;
}


/*
 sbrk
 Increase program data space.
 Malloc and related functions depend on this
 */
caddr_t _sbrk(int incr) {
    return (caddr_t)-1;
}

/*
 read
 Read a character to a file. `libc' subroutines will use this system routine for input from all files, including stdin
 Returns -1 on error or blocks until the number of characters have been read.
 */


int _read_r(struct _reent *ptr, int file, char *c, int len) {
    ptr->_errno = EBADF;
    return -1;
}

/*
 stat
 Status of a file (by name). Minimal implementation:
 int    _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
 */

int _stat_r(struct _reent *ptr, const char *filepath, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 times
 Timing information for current process. Minimal implementation:
 */

clock_t _times(struct tms *buf) {
    return -1;
}

/*
 unlink
 Remove a file's directory entry. Minimal implementation:
 */
int _unlink(char *name) {
    errno = ENOENT;
    return -1;
}

/*
 wait
 Wait for a child process. Minimal implementation:
 */
int _wait(int *status) {
    errno = ECHILD;
    return -1;
}

/*
 write
 Write a character to a file. `libc' subroutines will use this system routine for output to all files, including stdout
 Returns -1 on error or number of bytes sent
 */
int _write_r(struct _reent *ptr, int file, char *c, int len) {
    char *p = c;
    switch (file){
    case STDOUT_FILENO:
    case STDERR_FILENO:
	do{
            os_printf("%c", *p);    
        }while(++p < c + len);
    	return len;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        return -1;
    }
}

void* malloc(size_t size) {
    return os_malloc(size);
}

void free(void* ptr) {
    os_free(ptr);
}

void* realloc(void* ptr, size_t size) {
    return os_realloc(ptr, size);
}


void* _malloc_r(struct _reent *rptr, size_t size) {
    return os_malloc(size);
}

void _free_r(struct _reent *rptr, void* ptr) {
    os_free(ptr);
}

void* _realloc_r(struct _reent *rptr, void* ptr, size_t size) {
    return os_realloc(ptr, size);
}

void* _calloc_r(struct _reent *rptr, size_t num, size_t size) {
    void *ptr = os_malloc(num * size);
    os_bzero(ptr, num * size);
    return ptr;
}

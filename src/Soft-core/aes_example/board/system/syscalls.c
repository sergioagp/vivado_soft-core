/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include "../uart/uart.h"

#define UNUSED(x) (void)(x)

/* Variables */
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));


char *__env[1] = { 0 };
char **environ = __env;


/* Functions */
void initialise_monitor_handles()
{
}

int _getpid(void)
{
	return 1;
}

int _kill(int pid, int sig)
{
    UNUSED(pid);
    UNUSED(sig);
    
	errno = EINVAL;
	return -1;
}

void _exit (int status)
{
	_kill(status, -1);
	while (1) {}		/* Make sure we hang here */
}

int _read(int file, char *ptr, int len)
{
    UNUSED(file);
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		*ptr++ = __io_getchar();
	}

return len;
}

int _write(int file, char *ptr, int len)
{
    UNUSED(file);
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}
	return len;
}

int _close(int file)
{
    UNUSED(file);
	return -1;
}


int _fstat(int file, struct stat *st)
{
    UNUSED(file);
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int file)
{
    UNUSED(file);
	return 1;
}

int _lseek(int file, int ptr, int dir)
{
    UNUSED(file);
    UNUSED(ptr);
    UNUSED(dir);
	return 0;
}

int _open(char *path, int flags, ...)
{
    UNUSED(path);
    UNUSED(flags);
	/* Pretend like we always fail */
	return -1;
}

int _wait(int *status)
{
    UNUSED(status);
	errno = ECHILD;
	return -1;
}

int _unlink(char *name)
{
    UNUSED(name);
	errno = ENOENT;
	return -1;
}

int _times(struct tms *buf)
{
    UNUSED(buf);
	return -1;
}

int _stat(char *file, struct stat *st)
{
    UNUSED(file);
	st->st_mode = S_IFCHR;
	return 0;
}

int _link(char *old, char *new)
{
    UNUSED(old);
    UNUSED(new);
	errno = EMLINK;
	return -1;
}

int _fork(void)
{
	errno = EAGAIN;
	return -1;
}

int _execve(char *name, char **argv, char **env)
{
    UNUSED(name);
    UNUSED(argv);
    UNUSED(env);
	errno = ENOMEM;
	return -1;
}


#include <errno.h>
#include <limits.h>
#include <string.h>

#include <bits/ensure.h>
#include <mlibc/all-sysdeps.hpp>
#include <mlibc/debug.hpp>

namespace mlibc{


int sys_write(int fd, const void* buffer, size_t count, ssize_t* written){
	long ret = -1;//syscall(SYS_WRITE, fd, (uintptr_t)buffer, count);

	if(ret < 0)
		return -ret;

	*written = ret;
	return 0;
}

int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
	long ret = -1;//syscall(SYS_READ, fd, (uintptr_t)buf, count);

	if(ret < 0){
		*bytes_read = 0;
		return -ret;
	}

	*bytes_read = ret;
	return 0;
}

int sys_pwrite(int fd, const void* buffer, size_t count, off_t off, ssize_t* written){
	int ret = -1;// syscall(SYS_PWRITE, fd, (uintptr_t)buffer, count, 0, off);


	if(ret < 0){
		return -ret;
	}

	*written = ret;
	return 0;
}

int sys_pread(int fd, void *buf, size_t count, off_t off, ssize_t *bytes_read) {
	int ret =  -1;// syscall(SYS_PREAD, fd, (uintptr_t)buf, count, 0, off);

	if(ret < 0){
		return -ret;
	}

	*bytes_read = ret;
	return 0;
}

int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
	long ret = -1 ;//syscall(SYS_LSEEK, fd, offset, whence);

	if(ret < 0){
		return -ret;
	}

	*new_offset = ret;
	return 0;
}


int sys_open(const char* filename, int flags, mode_t mode, int* fd){
	long ret = -1;// syscall(SYS_OPEN, (uintptr_t)filename, flags);

	if(ret < 0)
		return -ret;

	*fd = ret;

	return 0;
}

int sys_close(int fd){
	// syscall(SYS_CLOSE, fd);
	return 0;
}

int sys_access(const char* filename, int mode){
	
	return 1;
}

int sys_stat(fsfd_target fsfdt, int fd, const char *path, int flags, struct stat *statbuf){
	long ret = 1;

	

	return -ret;
}

int sys_ioctl(int fd, unsigned long request, void *arg, int *result){
	long ret = -1 ;//syscall(SYS_IOCTL, fd, request, arg, result);

	if(ret < 0)
		return -ret;

	return 0;
}

#ifndef MLIBC_BUILDING_RTDL


int sys_mkdir(const char* path, mode_t){
	long ret = -1 ;//syscall(SYS_MKDIR, path);

	if(ret < 0){
		return -ret;
	}

	return 0;
}

int sys_rmdir(const char* path){
	long ret = -1;//syscall(SYS_RMDIR, path);

	if(ret < 0){
		return -ret;
	}

	return 0;
}

int sys_link(const char* srcpath, const char* destpath){
	long ret = -1;// syscall(SYS_LINK, srcpath, destpath);

	if(ret < 0){
		return -ret;
	}

	return 0;
}

int sys_unlinkat(int fd, const char *path, int flags) {
	long ret = -1;//syscall(SYS_UNLINK, fd, path, flags);

	if(ret < 0) {
		return -ret;
	}

	return 0;
}

typedef struct lemon_dirent {
	uint32_t inode; // Inode number
	uint32_t type;
	char name[NAME_MAX]; // Filename
} lemon_dirent_t;

int sys_read_entries(int handle, void *buffer, size_t max_size, size_t *bytes_read){
	return 1;
}

int sys_open_dir(const char* path, int* handle){
	// return sys_open(path, O_DIRECTORY, 0, handle);
        return 1;
}

int sys_rename(const char* path, const char* new_path){
	// return -syscall(SYS_RENAME, path, new_path);
        return 1;
}

int sys_readlink(const char *path, void *buffer, size_t max_size, ssize_t *length){
	long ret = 1;// syscall(SYS_READLINK, path, buffer, max_size);
	if(ret < 0){
		return -ret;
	}

	*length = ret;
	return 0;
}

int sys_dup(int fd, int flags, int* newfd){
	int ret = -1;//syscall(SYS_DUP, fd, flags, -1);
	if(ret < 0){
		return -ret;
	}

	*newfd = ret;
	return 0;
}

int sys_dup2(int fd, int flags, int newfd){
	int ret = -1;// syscall(SYS_DUP, fd, flags, newfd);
	if(ret < 0){
		return -ret;
	}

	return 0;
}

int sys_chmod(const char *pathname, mode_t mode){
	int ret = -1;//syscall(SYS_CHMOD, pathname, mode);

	if(ret < 0){
		return -ret;
	}

	return 0;
}

int sys_pipe(int *fds, int flags){
	// return -syscall(SYS_PIPE, fds, flags);
        return 1;
}

int sys_epoll_create(int flags, int *fd) {
	int ret = -1;//syscall(SYS_EPOLL_CREATE, flags);

	if(ret < 0){
		return -ret;
	}

	*fd = ret;

	return 0;
}

int sys_ttyname(int tty, char *buf, size_t size) {
	
	return ENODEV;
}

int sys_fchdir(int fd) {
	// return syscall(SYS_FCHDIR, fd);
        return 1;
}
#endif

}

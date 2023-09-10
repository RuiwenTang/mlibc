#include <stddef.h>
#include <bits/ensure.h>
#include <abi-bits/pid_t.h>
#include <mlibc/debug.hpp>
#include <mlibc/all-sysdeps.hpp>
#include <errno.h>

namespace mlibc{

int sys_futex_tid(){
	return 0;
}

int sys_futex_wait(int *pointer, int expected, const struct timespec *time){
	return -1;
}

int sys_futex_wake(int *pointer) {
	return -1;
}

int sys_tcb_set(void* pointer){
	// syscall(SYS_SET_FS_BASE, (uintptr_t)pointer);
	return 0;
}

int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
	__ensure(flags & MAP_ANONYMOUS);

	// return syscall(SYS_MMAP, (uintptr_t)window, (size + 0xFFF) & ~static_cast<size_t>(0xFFF), (uintptr_t)hint, flags);
        return -1;
}

int sys_vm_unmap(void* address, size_t size) {
	__ensure(!(size & 0xFFF));

	// long ret = syscall(SYS_MUNMAP, (uintptr_t)address, (size + 0xFFF) & ~static_cast<size_t>(0xFFF));
        int ret = -1;

	return ret;
}

int sys_anon_allocate(size_t size, void **pointer) {
	return sys_vm_map(nullptr, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0, pointer);
}

int sys_anon_free(void *pointer, size_t size) {
	return sys_vm_unmap(pointer, size);
}

void sys_libc_panic(){
	sys_libc_log("libc panic!");
	__builtin_trap();
	for(;;);
}

void sys_libc_log(const char* msg){
	// syscall(0, (uintptr_t)msg);
}

#ifndef MLIBC_BUILDING_RTDL

void sys_exit(int status){
	// syscall(SYS_EXIT, status);

	__builtin_unreachable();
}

pid_t sys_getpid(){
	uint64_t _pid;
	// syscall(SYS_GETPID, (uintptr_t)&_pid);

	pid_t pid = _pid;
	return pid;
}

pid_t sys_getppid(){
	// return syscall(SYS_GETPPID);
        return 0;
}

int sys_clock_get(int clock, time_t *secs, long *nanos) {
	// syscall(SYS_UPTIME, nanos);

	*secs = (*nanos) / 1000000000;
	*nanos = (*nanos) - (*secs) * 1000000000;

	return 0;
}

int sys_getcwd(char *buffer, size_t size){
	// return syscall(SYS_GET_CWD, buffer, size);
        return -1;
}

int sys_chdir(const char *path){
	// syscall(SYS_CHDIR, path);
	return 0;
}

int sys_sleep(time_t* sec, long* nanosec){
	// syscall(SYS_NANO_SLEEP, (*sec) * 1000000000 + (*nanosec));
	return 0;
}

uid_t sys_getuid(){
	// return syscall(SYS_GETUID);
        return 0;
}

uid_t sys_geteuid(){
	// return syscall(SYS_GETEUID);
        return 0;
}

int sys_setuid(uid_t uid){
	// return -syscall(SYS_SETUID, uid);
        return 0;
}

int sys_seteuid(uid_t euid){
	// return -syscall(SYS_SETEUID, euid);
        return 0;
}

gid_t sys_getgid(){
	// return syscall(SYS_GETGID);
        return 0;
}

gid_t sys_getegid(){
	// return syscall(SYS_GETEGID);
        return 0;
}

int sys_setgid(gid_t gid){
	mlibc::infoLogger() << "mlibc: sys_setgid is a stub" << frg::endlog;
	return 0;
}

int sys_setegid(gid_t egid){
	mlibc::infoLogger() << "mlibc: sys_setegid is a stub" << frg::endlog;
	return 0;
}

void sys_yield(){
	// syscall(SYS_YIELD);
}

int sys_clone(void *tcb, pid_t *tid_out, void *stack){
	pid_t tid = -1; // syscall(SYS_SPAWN_THREAD, __mlibc_start_thread, stack);

	if(tid < 0){
		errno = tid;
		return -1;
	}

	*tid_out = tid;

	return 0;
}

void sys_thread_exit(){
	// syscall(SYS_EXIT_THREAD);

	__builtin_unreachable();
}

int sys_waitpid(pid_t pid, int *status, int flags, struct rusage *ru, pid_t *ret_pid){
	if(ru) {
		mlibc::infoLogger() << "mlibc: struct rusage in sys_waitpid is unsupported" << frg::endlog;
		return ENOSYS;
	}

	pid_t ret = -1; //syscall(SYS_WAIT_PID, pid, status, flags);

	if(ret < 0){
		return -ret;
	}

	*ret_pid = ret;

	return 0;
}

int sys_fork(pid_t *child){
	long pid = -1; //syscall(SYS_FORK, 0);
	if(pid < 0){
		errno = pid;
		return -1;
	}

	*child = pid;
	return 0;
}

int sys_execve(const char *path, char *const argv[], char *const envp[]){
	// return -syscall(SYS_EXECVE, path, argv, envp);
        return 0;
}

int sys_getentropy(void *buffer, size_t length){
	// return -syscall(SYS_GETENTROPY, buffer, length);
        return 0;
}
#endif

}
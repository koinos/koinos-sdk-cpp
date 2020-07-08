
#include <koinos/system/koinos_api.h>

#include <wasi/api.h>

/**
 * Read command-line argument data.
 * The size of the array should match that returned by `args_sizes_get`
 */
__wasi_errno_t __wasi_args_get(
    uint8_t * * argv,
    uint8_t * argv_buf
)
{
   return __WASI_ERRNO_SUCCESS;
}

/**
 * Return command-line argument data sizes.
 */
__wasi_errno_t __wasi_args_sizes_get(
    /**
     * The number of arguments.
     */
    __wasi_size_t *argc,
    /**
     * The size of the argument string data.
     */
    __wasi_size_t *argv_buf_size
)
{
   (*argc) = 0;
   (*argv_buf_size) = 0;
   return __WASI_ERRNO_SUCCESS;
}

/**
 * Read environment variable data.
 * The sizes of the buffers should match that returned by `environ_sizes_get`.
 */
__wasi_errno_t __wasi_environ_get(
    uint8_t * * environ,
    uint8_t * environ_buf
)
{
   return __WASI_ERRNO_SUCCESS;
}

/**
 * Return environment variable data sizes.
 */
__wasi_errno_t __wasi_environ_sizes_get(
    /**
     * The number of environment variable arguments.
     */
    __wasi_size_t *environc,
    /**
     * The size of the environment variable data.
     */
    __wasi_size_t *environ_buf_size
)
{
   (*environc) = 0;
   (*environ_buf_size) = 0;
   return __WASI_ERRNO_SUCCESS;
}

/**
 * Return the resolution of a clock.
 * Implementations are required to provide a non-zero value for supported clocks. For unsupported clocks,
 * return `errno::inval`.
 * Note: This is similar to `clock_getres` in POSIX.
 */
__wasi_errno_t __wasi_clock_res_get(
    /**
     * The clock for which to return the resolution.
     */
    __wasi_clockid_t id,

    /**
     * The resolution of the clock.
     */
    __wasi_timestamp_t *resolution
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Return the time value of a clock.
 * Note: This is similar to `clock_gettime` in POSIX.
 */
__wasi_errno_t __wasi_clock_time_get(
    /**
     * The clock for which to return the time.
     */
    __wasi_clockid_t id,

    /**
     * The maximum lag (exclusive) that the returned time value may have, compared to its actual value.
     */
    __wasi_timestamp_t precision,

    /**
     * The time value of the clock.
     */
    __wasi_timestamp_t *time
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Provide file advisory information on a file descriptor.
 * Note: This is similar to `posix_fadvise` in POSIX.
 */
__wasi_errno_t __wasi_fd_advise(
    __wasi_fd_t fd,

    /**
     * The offset within the file to which the advisory applies.
     */
    __wasi_filesize_t offset,

    /**
     * The length of the region to which the advisory applies.
     */
    __wasi_filesize_t len,

    /**
     * The advice.
     */
    __wasi_advice_t advice
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Force the allocation of space in a file.
 * Note: This is similar to `posix_fallocate` in POSIX.
 */
__wasi_errno_t __wasi_fd_allocate(
    __wasi_fd_t fd,

    /**
     * The offset at which to start the allocation.
     */
    __wasi_filesize_t offset,

    /**
     * The length of the area that is allocated.
     */
    __wasi_filesize_t len
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Close a file descriptor.
 * Note: This is similar to `close` in POSIX.
 */
__wasi_errno_t __wasi_fd_close(
    __wasi_fd_t fd
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Synchronize the data of a file to disk.
 * Note: This is similar to `fdatasync` in POSIX.
 */
__wasi_errno_t __wasi_fd_datasync(
    __wasi_fd_t fd
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Get the attributes of a file descriptor.
 * Note: This returns similar flags to `fsync(fd, F_GETFL)` in POSIX, as well as additional fields.
 */
__wasi_errno_t __wasi_fd_fdstat_get(
    __wasi_fd_t fd,

    /**
     * The buffer where the file descriptor's attributes are stored.
     */
    __wasi_fdstat_t *stat
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Adjust the flags associated with a file descriptor.
 * Note: This is similar to `fcntl(fd, F_SETFL, flags)` in POSIX.
 */
__wasi_errno_t __wasi_fd_fdstat_set_flags(
    __wasi_fd_t fd,

    /**
     * The desired values of the file descriptor flags.
     */
    __wasi_fdflags_t flags
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Adjust the rights associated with a file descriptor.
 * This can only be used to remove rights, and returns `errno::notcapable` if called in a way that would attempt to add rights
 */
__wasi_errno_t __wasi_fd_fdstat_set_rights(
    __wasi_fd_t fd,

    /**
     * The desired rights of the file descriptor.
     */
    __wasi_rights_t fs_rights_base,

    __wasi_rights_t fs_rights_inheriting
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Return the attributes of an open file.
 */
__wasi_errno_t __wasi_fd_filestat_get(
    __wasi_fd_t fd,

    /**
     * The buffer where the file's attributes are stored.
     */
    __wasi_filestat_t *buf
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Adjust the size of an open file. If this increases the file's size, the extra bytes are filled with zeros.
 * Note: This is similar to `ftruncate` in POSIX.
 */
__wasi_errno_t __wasi_fd_filestat_set_size(
    __wasi_fd_t fd,

    /**
     * The desired file size.
     */
    __wasi_filesize_t size
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Adjust the timestamps of an open file or directory.
 * Note: This is similar to `futimens` in POSIX.
 */
__wasi_errno_t __wasi_fd_filestat_set_times(
    __wasi_fd_t fd,

    /**
     * The desired values of the data access timestamp.
     */
    __wasi_timestamp_t atim,

    /**
     * The desired values of the data modification timestamp.
     */
    __wasi_timestamp_t mtim,

    /**
     * A bitmask indicating which timestamps to adjust.
     */
    __wasi_fstflags_t fst_flags
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Read from a file descriptor, without using and updating the file descriptor's offset.
 * Note: This is similar to `preadv` in POSIX.
 */
__wasi_errno_t __wasi_fd_pread(
    __wasi_fd_t fd,

    /**
     * List of scatter/gather vectors in which to store data.
     */
    const __wasi_iovec_t *iovs,

    /**
     * The length of the array pointed to by `iovs`.
     */
    size_t iovs_len,

    /**
     * The offset within the file at which to read.
     */
    __wasi_filesize_t offset,

    /**
     * The number of bytes read.
     */
    __wasi_size_t *nread
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Return a description of the given preopened file descriptor.
 */
__wasi_errno_t __wasi_fd_prestat_get(
    __wasi_fd_t fd,

    /**
     * The buffer where the description is stored.
     */
    __wasi_prestat_t *buf
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Return a description of the given preopened file descriptor.
 */
__wasi_errno_t __wasi_fd_prestat_dir_name(
    __wasi_fd_t fd,

    /**
     * A buffer into which to write the preopened directory name.
     */
    uint8_t * path,

    __wasi_size_t path_len
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Write to a file descriptor, without using and updating the file descriptor's offset.
 * Note: This is similar to `pwritev` in POSIX.
 */
__wasi_errno_t __wasi_fd_pwrite(
    __wasi_fd_t fd,

    /**
     * List of scatter/gather vectors from which to retrieve data.
     */
    const __wasi_ciovec_t *iovs,

    /**
     * The length of the array pointed to by `iovs`.
     */
    size_t iovs_len,

    /**
     * The offset within the file at which to write.
     */
    __wasi_filesize_t offset,

    /**
     * The number of bytes written.
     */
    __wasi_size_t *nwritten
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Read from a file descriptor.
 * Note: This is similar to `readv` in POSIX.
 */
__wasi_errno_t __wasi_fd_read(
    __wasi_fd_t fd,

    /**
     * List of scatter/gather vectors to which to store data.
     */
    const __wasi_iovec_t *iovs,

    /**
     * The length of the array pointed to by `iovs`.
     */
    size_t iovs_len,

    /**
     * The number of bytes read.
     */
    __wasi_size_t *nread
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Read directory entries from a directory.
 * When successful, the contents of the output buffer consist of a sequence of
 * directory entries. Each directory entry consists of a dirent_t object,
 * followed by dirent_t::d_namlen bytes holding the name of the directory
 * entry.
 * This function fills the output buffer as much as possible, potentially
 * truncating the last directory entry. This allows the caller to grow its
 * read buffer size in case it's too small to fit a single large directory
 * entry, or skip the oversized directory entry.
 */
__wasi_errno_t __wasi_fd_readdir(
    __wasi_fd_t fd,

    /**
     * The buffer where directory entries are stored
     */
    uint8_t * buf,

    __wasi_size_t buf_len,

    /**
     * The location within the directory to start reading
     */
    __wasi_dircookie_t cookie,

    /**
     * The number of bytes stored in the read buffer. If less than the size of the read buffer, the end of the directory has been reached.
     */
    __wasi_size_t *bufused
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Atomically replace a file descriptor by renumbering another file descriptor.
 * Due to the strong focus on thread safety, this environment does not provide
 * a mechanism to duplicate or renumber a file descriptor to an arbitrary
 * number, like `dup2()`. This would be prone to race conditions, as an actual
 * file descriptor with the same number could be allocated by a different
 * thread at the same time.
 * This function provides a way to atomically renumber file descriptors, which
 * would disappear if `dup2()` were to be removed entirely.
 */
__wasi_errno_t __wasi_fd_renumber(
    __wasi_fd_t fd,

    /**
     * The file descriptor to overwrite.
     */
    __wasi_fd_t to
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Move the offset of a file descriptor.
 * Note: This is similar to `lseek` in POSIX.
 */
__wasi_errno_t __wasi_fd_seek(
    __wasi_fd_t fd,

    /**
     * The number of bytes to move.
     */
    __wasi_filedelta_t offset,

    /**
     * The base from which the offset is relative.
     */
    __wasi_whence_t whence,

    /**
     * The new offset of the file descriptor, relative to the start of the file.
     */
    __wasi_filesize_t *newoffset
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Synchronize the data and metadata of a file to disk.
 * Note: This is similar to `fsync` in POSIX.
 */
__wasi_errno_t __wasi_fd_sync(
    __wasi_fd_t fd
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Return the current offset of a file descriptor.
 * Note: This is similar to `lseek(fd, 0, SEEK_CUR)` in POSIX.
 */
__wasi_errno_t __wasi_fd_tell(
    __wasi_fd_t fd,

    /**
     * The current offset of the file descriptor, relative to the start of the file.
     */
    __wasi_filesize_t *offset
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Write to a file descriptor.
 * Note: This is similar to `writev` in POSIX.
 */
__wasi_errno_t __wasi_fd_write(
    __wasi_fd_t fd,

    /**
     * List of scatter/gather vectors from which to retrieve data.
     */
    const __wasi_ciovec_t *iovs,

    /**
     * The length of the array pointed to by `iovs`.
     */
    size_t iovs_len,

    /**
     * The number of bytes written.
     */
    __wasi_size_t *nwritten
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Create a directory.
 * Note: This is similar to `mkdirat` in POSIX.
 */
__wasi_errno_t __wasi_path_create_directory(
    __wasi_fd_t fd,

    /**
     * The path at which to create the directory.
     */
    const char *path,

    /**
     * The length of the buffer pointed to by `path`.
     */
    size_t path_len
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Return the attributes of a file or directory.
 * Note: This is similar to `stat` in POSIX.
 */
__wasi_errno_t __wasi_path_filestat_get(
    __wasi_fd_t fd,

    /**
     * Flags determining the method of how the path is resolved.
     */
    __wasi_lookupflags_t flags,

    /**
     * The path of the file or directory to inspect.
     */
    const char *path,

    /**
     * The length of the buffer pointed to by `path`.
     */
    size_t path_len,

    /**
     * The buffer where the file's attributes are stored.
     */
    __wasi_filestat_t *buf
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Adjust the timestamps of a file or directory.
 * Note: This is similar to `utimensat` in POSIX.
 */
__wasi_errno_t __wasi_path_filestat_set_times(
    __wasi_fd_t fd,

    /**
     * Flags determining the method of how the path is resolved.
     */
    __wasi_lookupflags_t flags,

    /**
     * The path of the file or directory to operate on.
     */
    const char *path,

    /**
     * The length of the buffer pointed to by `path`.
     */
    size_t path_len,

    /**
     * The desired values of the data access timestamp.
     */
    __wasi_timestamp_t atim,

    /**
     * The desired values of the data modification timestamp.
     */
    __wasi_timestamp_t mtim,

    /**
     * A bitmask indicating which timestamps to adjust.
     */
    __wasi_fstflags_t fst_flags
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Create a hard link.
 * Note: This is similar to `linkat` in POSIX.
 */
__wasi_errno_t __wasi_path_link(
    __wasi_fd_t old_fd,

    /**
     * Flags determining the method of how the path is resolved.
     */
    __wasi_lookupflags_t old_flags,

    /**
     * The source path from which to link.
     */
    const char *old_path,

    /**
     * The length of the buffer pointed to by `old_path`.
     */
    size_t old_path_len,

    /**
     * The working directory at which the resolution of the new path starts.
     */
    __wasi_fd_t new_fd,

    /**
     * The destination path at which to create the hard link.
     */
    const char *new_path,

    /**
     * The length of the buffer pointed to by `new_path`.
     */
    size_t new_path_len
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Open a file or directory.
 * The returned file descriptor is not guaranteed to be the lowest-numbered
 * file descriptor not currently open; it is randomized to prevent
 * applications from depending on making assumptions about indexes, since this
 * is error-prone in multi-threaded contexts. The returned file descriptor is
 * guaranteed to be less than 2**31.
 * Note: This is similar to `openat` in POSIX.
 */
__wasi_errno_t __wasi_path_open(
    __wasi_fd_t fd,

    /**
     * Flags determining the method of how the path is resolved.
     */
    __wasi_lookupflags_t dirflags,

    /**
     * The relative path of the file or directory to open, relative to the
     * `path_open::fd` directory.
     */
    const char *path,

    /**
     * The length of the buffer pointed to by `path`.
     */
    size_t path_len,

    /**
     * The method by which to open the file.
     */
    __wasi_oflags_t oflags,

    /**
     * The initial rights of the newly created file descriptor. The
     * implementation is allowed to return a file descriptor with fewer rights
     * than specified, if and only if those rights do not apply to the type of
     * file being opened.
     * The *base* rights are rights that will apply to operations using the file
     * descriptor itself, while the *inheriting* rights are rights that apply to
     * file descriptors derived from it.
     */
    __wasi_rights_t fs_rights_base,

    __wasi_rights_t fs_rights_inherting,

    __wasi_fdflags_t fdflags,

    /**
     * The file descriptor of the file that has been opened.
     */
    __wasi_fd_t *opened_fd
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Read the contents of a symbolic link.
 * Note: This is similar to `readlinkat` in POSIX.
 */
__wasi_errno_t __wasi_path_readlink(
    __wasi_fd_t fd,

    /**
     * The path of the symbolic link from which to read.
     */
    const char *path,

    /**
     * The length of the buffer pointed to by `path`.
     */
    size_t path_len,

    /**
     * The buffer to which to write the contents of the symbolic link.
     */
    uint8_t * buf,

    __wasi_size_t buf_len,

    /**
     * The number of bytes placed in the buffer.
     */
    __wasi_size_t *bufused
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Remove a directory.
 * Return `errno::notempty` if the directory is not empty.
 * Note: This is similar to `unlinkat(fd, path, AT_REMOVEDIR)` in POSIX.
 */
__wasi_errno_t __wasi_path_remove_directory(
    __wasi_fd_t fd,

    /**
     * The path to a directory to remove.
     */
    const char *path,

    /**
     * The length of the buffer pointed to by `path`.
     */
    size_t path_len
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Rename a file or directory.
 * Note: This is similar to `renameat` in POSIX.
 */
__wasi_errno_t __wasi_path_rename(
    __wasi_fd_t fd,

    /**
     * The source path of the file or directory to rename.
     */
    const char *old_path,

    /**
     * The length of the buffer pointed to by `old_path`.
     */
    size_t old_path_len,

    /**
     * The working directory at which the resolution of the new path starts.
     */
    __wasi_fd_t new_fd,

    /**
     * The destination path to which to rename the file or directory.
     */
    const char *new_path,

    /**
     * The length of the buffer pointed to by `new_path`.
     */
    size_t new_path_len
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Create a symbolic link.
 * Note: This is similar to `symlinkat` in POSIX.
 */
__wasi_errno_t __wasi_path_symlink(
    /**
     * The contents of the symbolic link.
     */
    const char *old_path,

    /**
     * The length of the buffer pointed to by `old_path`.
     */
    size_t old_path_len,

    __wasi_fd_t fd,

    /**
     * The destination path at which to create the symbolic link.
     */
    const char *new_path,

    /**
     * The length of the buffer pointed to by `new_path`.
     */
    size_t new_path_len
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Unlink a file.
 * Return `errno::isdir` if the path refers to a directory.
 * Note: This is similar to `unlinkat(fd, path, 0)` in POSIX.
 */
__wasi_errno_t __wasi_path_unlink_file(
    __wasi_fd_t fd,

    /**
     * The path to a file to unlink.
     */
    const char *path,

    /**
     * The length of the buffer pointed to by `path`.
     */
    size_t path_len
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Concurrently poll for the occurrence of a set of events.
 */
__wasi_errno_t __wasi_poll_oneoff(
    /**
     * The events to which to subscribe.
     */
    const __wasi_subscription_t * in,

    /**
     * The events that have occurred.
     */
    __wasi_event_t * out,

    /**
     * Both the number of subscriptions and events.
     */
    __wasi_size_t nsubscriptions,

    /**
     * The number of events stored.
     */
    __wasi_size_t *nevents
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Terminate the process normally. An exit code of 0 indicates successful
 * termination of the program. The meanings of other values is dependent on
 * the environment.
 */
_Noreturn void __wasi_proc_exit(
    /**
     * The exit code returned by the process.
     */
    __wasi_exitcode_t rval
)
{
   koinos_exit( rval );
}

/**
 * Send a signal to the process of the calling thread.
 * Note: This is similar to `raise` in POSIX.
 */
__wasi_errno_t __wasi_proc_raise(
    /**
     * The signal condition to trigger.
     */
    __wasi_signal_t sig
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Temporarily yield execution of the calling thread.
 * Note: This is similar to `sched_yield` in POSIX.
 */
__wasi_errno_t __wasi_sched_yield(
    void
)
{
   return __WASI_ERRNO_SUCCESS;
}

/**
 * Write high-quality random data into a buffer.
 * This function blocks when the implementation is unable to immediately
 * provide sufficient high-quality random data.
 * This function may execute slowly, so when large mounts of random data are
 * required, it's advisable to use this function to seed a pseudo-random
 * number generator, rather than to provide the random data directly.
 */
__wasi_errno_t __wasi_random_get(
    /**
     * The buffer to fill with random data.
     */
    uint8_t * buf,

    __wasi_size_t buf_len
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Receive a message from a socket.
 * Note: This is similar to `recv` in POSIX, though it also supports reading
 * the data into multiple buffers in the manner of `readv`.
 */
__wasi_errno_t __wasi_sock_recv(
    __wasi_fd_t fd,

    /**
     * List of scatter/gather vectors to which to store data.
     */
    const __wasi_iovec_t *ri_data,

    /**
     * The length of the array pointed to by `ri_data`.
     */
    size_t ri_data_len,

    /**
     * Message flags.
     */
    __wasi_riflags_t ri_flags,

    /**
     * Number of bytes stored in ri_data.
     */
    __wasi_size_t *ro_datalen,
    /**
     * Message flags.
     */
    __wasi_roflags_t *ro_flags
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Send a message on a socket.
 * Note: This is similar to `send` in POSIX, though it also supports writing
 * the data from multiple buffers in the manner of `writev`.
 */
__wasi_errno_t __wasi_sock_send(
    __wasi_fd_t fd,

    /**
     * List of scatter/gather vectors to which to retrieve data
     */
    const __wasi_ciovec_t *si_data,

    /**
     * The length of the array pointed to by `si_data`.
     */
    size_t si_data_len,

    /**
     * Message flags.
     */
    __wasi_siflags_t si_flags,

    /**
     * Number of bytes transmitted.
     */
    __wasi_size_t *so_datalen
)
{
   return __WASI_ERRNO_ACCES;
}

/**
 * Shut down socket send and receive channels.
 * Note: This is similar to `shutdown` in POSIX.
 */
__wasi_errno_t __wasi_sock_shutdown(
    __wasi_fd_t fd,

    /**
     * Which channels on the socket to shut down.
     */
    __wasi_sdflags_t how
)
{
   return __WASI_ERRNO_ACCES;
}

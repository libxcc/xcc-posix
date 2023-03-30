#ifndef			_XCC_POSIX_FILESYSTEM_H_
#define			_XCC_POSIX_FILESYSTEM_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN


// Maximum allowed path length
#define 		X_FS_MAX_NAME					(256)
#define 		X_FS_MAX_PATH					XCC_PATH_MAX

// Filesystem lookup context data
typedef struct x_fs_find_data
{
#if defined(XCC_SYSTEM_WINDOWS)
	int64_t			handle;
#else
	void*			handle;
#endif
	char 			dir[X_FS_MAX_PATH];
}*x_fs_find_t;

// File stat information
#if defined(XCC_SYSTEM_WINDOWS)
typedef				struct _stat64			x_file_stat_t;
#else
typedef				struct stat			x_file_stat_t;
#endif

// File attribute information
typedef struct x_file_data_t
{
	char 			dir[X_FS_MAX_PATH];		// Directory name
	char 			path[X_FS_MAX_PATH];		// File full path
	char 			name[X_FS_MAX_NAME];		// File name
	uint64_t 		size;				// File size
	uint32_t 		mode;				// File type and access rights
	int64_t			atime;				// Last visited time
	int64_t			mtime;				// Last modified time
	int64_t			ctime;				// Create time
}x_file_data_t;

// Filesystem disk space information
typedef struct x_fs_space_t
{
	uint64_t		avail_bytes;
	uint64_t 		free_bytes;
	uint64_t		total_bytes;
}x_fs_space_t;



// posix : dirname
_XPOSIXAPI_ char* __xcall__ x_posix_dirname(char* _FilePath);

// posix : basename
_XPOSIXAPI_ char* __xcall__ x_posix_basename(char* _FilePath);



// posix : wdirname
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wdirname(wchar_t* _FilePath);

// posix : wbasename
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wbasename(wchar_t* _FilePath);



// posix : dup
_XPOSIXAPI_ int __xcall__ x_posix_dup(int _FileHandle);

// posix : dup2
_XPOSIXAPI_ int __xcall__ x_posix_dup2(int _FileHandleSrc, int _FileHandleDst);

// posix : open
_XPOSIXAPI_ int __xcall__ x_posix_open(const char* _Filename, int _Flag, ...);

// posix : lseek
_XPOSIXAPI_ off_t __xcall__ x_posix_lseek(int _FileHandle, off_t _Offset, int _Origin);

// posix : read
_XPOSIXAPI_ ssize_t __xcall__ x_posix_read(int _FileHandle, void* _Buffer, size_t _Count);

// posix : write
_XPOSIXAPI_ ssize_t __xcall__ x_posix_write(int _FileHandle, const void* _Buffer, size_t _Count);

// posix : close
_XPOSIXAPI_ int __xcall__ x_posix_close(int _FileHandle);

// posix : sync
_XPOSIXAPI_ void __xcall__ x_posix_sync(void);



// posix : access
_XPOSIXAPI_ int __xcall__ x_posix_access(const char* _Path, int _Mode);

// posix : mkdir
_XPOSIXAPI_ int __xcall__ x_posix_mkdir(const char* _Directory, mode_t _Mode);

// posix : mkdir_r
_XPOSIXAPI_ int __xcall__ x_posix_mkdir_r(const char* _Directory, mode_t _Mode);

// posix : chmod
_XPOSIXAPI_ int __xcall__ x_posix_chmod(const char* _Path, int _Mode);

// posix : rmdir
_XPOSIXAPI_ int __xcall__ x_posix_rmdir(const char* _Path);

// posix : rmdir_r
_XPOSIXAPI_ int __xcall__ x_posix_rmdir_r(const char* _Path);

// posix : remove
_XPOSIXAPI_ int __xcall__ x_posix_remove(const char* _FileName);

// posix : rename
_XPOSIXAPI_ int __xcall__ x_posix_rename(const char* _OldFileName, const char* _NewFileName);

// posix : unlink
_XPOSIXAPI_ int __xcall__ x_posix_unlink(const char* _FileName);

// posix : tmpfile
_XPOSIXAPI_ FILE* __xcall__ x_posix_tmpfile(void);



// posix : waccess
_XPOSIXAPI_ int __xcall__ x_posix_waccess(const wchar_t* _Path, int _Mode);

// posix : wmkdir
_XPOSIXAPI_ int __xcall__ x_posix_wmkdir(const wchar_t* _Directory, mode_t _Mode);

// posix : wmkdir_r
_XPOSIXAPI_ int __xcall__ x_posix_wmkdir_r(const wchar_t* _Directory, mode_t _Mode);

// posix : wchmod
_XPOSIXAPI_ int __xcall__ x_posix_wchmod(const wchar_t* _Path, int _Mode);

// posix : wrmdir
_XPOSIXAPI_ int __xcall__ x_posix_wrmdir(const wchar_t* _Path);

// posix : wrmdir_r
_XPOSIXAPI_ int __xcall__ x_posix_wrmdir_r(const wchar_t* _Path);

// posix : wremove
_XPOSIXAPI_ int __xcall__ x_posix_wremove(const wchar_t* _FileName);

// posix : wrename
_XPOSIXAPI_ int __xcall__ x_posix_wrename(const wchar_t* _OldFileName, const wchar_t* _NewFileName);

// posix : wunlink
_XPOSIXAPI_ int __xcall__ x_posix_wunlink(const wchar_t* _FileName);



// posix : fopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_fopen(const char* _Filename, const char* _Mode);

// posix : fdopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_fdopen(int _Fildes, const char* _Mode);

// posix : freopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_freopen(const char* _Filename, const char* _Mode, FILE* _Stream);



// posix : wfopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_wfopen(const wchar_t* _Filename, const wchar_t* _Mode);

// posix : wfdopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_wfdopen(int _Fildes, const wchar_t* _Mode);

// posix : wfreopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_wfreopen(const wchar_t* _Filename, const wchar_t* _Mode, FILE* _Stream);



// posix : fileno
_XPOSIXAPI_ int __xcall__ x_posix_fileno(FILE* _Stream);

// posix : fseek
_XPOSIXAPI_ int __xcall__ x_posix_fseek(FILE* _Stream, long _Offset, int _Whence);

// posix : fseek64
_XPOSIXAPI_ int64_t __xcall__ x_posix_fseek64(FILE* _Stream, int64_t _Offset, int _Whence);

// posix : ftell
_XPOSIXAPI_ long __xcall__ x_posix_ftell(FILE* _Stream);

// posix : ftell64
_XPOSIXAPI_ int64_t __xcall__ x_posix_ftell64(FILE* _Stream);

// posix : rewind
_XPOSIXAPI_ void __xcall__ x_posix_rewind(FILE* _Stream);

// posix : fgetc
_XPOSIXAPI_ int __xcall__ x_posix_fgetc(FILE* _Stream);

// posix : fputc
_XPOSIXAPI_ int __xcall__ x_posix_fputc(int _Character, FILE* _Stream);

// posix : fgets
_XPOSIXAPI_ char* __xcall__ x_posix_fgets(char* _Buffer, int _MaxCount, FILE* _Stream);

// posix : fputs
_XPOSIXAPI_ int __xcall__ x_posix_fputs(const char* _Buffer, FILE* _Stream);

// posix : fread
_XPOSIXAPI_ size_t __xcall__ x_posix_fread(void* _Memory, size_t _Size, size_t _Item, FILE* _Stream);

// posix : fwrite
_XPOSIXAPI_ size_t __xcall__ x_posix_fwrite(const void* _Memory, size_t _Size, size_t _Item, FILE* _Stream);

// posix : feof
_XPOSIXAPI_ int __xcall__ x_posix_feof(FILE* _Stream);

// posix : ferror
_XPOSIXAPI_ int __xcall__ x_posix_ferror(FILE* _Stream);

// posix : fsync
_XPOSIXAPI_ int __xcall__ x_posix_fsync(int _Fildes);

// posix : fclose
_XPOSIXAPI_ int __xcall__ x_posix_fclose(FILE* _Stream);

// posix : fsize
_XPOSIXAPI_ unsigned long long __xcall__ x_posix_fsize(const char* _Filename);



// posix : opendir
_XPOSIXAPI_ DIR* __xcall__ x_posix_opendir(const char* _Name);

// posix : readdir
_XPOSIXAPI_ struct dirent* __xcall__ x_posix_readdir(DIR* _Stream);

// posix : closedir
_XPOSIXAPI_ int __xcall__ x_posix_closedir(DIR* _Stream);



// FS: Convert path to common format
_XPOSIXAPI_ char* __xcall__ x_fs_path_to_common(const char* _SrcPath);

// FS: Convert path to native format
_XPOSIXAPI_ char* __xcall__ x_fs_path_to_native(const char* _SrcPath);

// FS: Find the last delimiter
_XPOSIXAPI_ const char* __xcall__ x_fs_path_find_last_div(const char* _FilePath);



// FS: Query the space information of the specified partition
_XPOSIXAPI_ int __xcall__ x_fs_disk_space(const char* _Path, x_fs_space_t* _Space);



// FS: Open the specified directory and return to the first child node
_XPOSIXAPI_ x_fs_find_t __xcall__ x_fs_find_first(const char* _Directory, x_file_data_t* _FileData);

// FS: Find the next name. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int __xcall__ x_fs_find_next(x_fs_find_t _Stream, x_file_data_t* _FileData);

// FS: This function closes the specified search handle. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int __xcall__ x_fs_find_close(x_fs_find_t _Stream);



// FS: Does the path exist
_XPOSIXAPI_ bool __xcall__ x_fs_path_exists(const char* _FilePath);

// Gets information about the file the path points to
_XPOSIXAPI_ int __xcall__ x_fs_path_stat(const char* _FilePath, x_file_stat_t* _Stat);

// Analog CXX : std_filesystem_is_block_file
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_block_file(x_uint32_t _StatMode);

// Analog CXX : std_filesystem_is_character_file
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_character_file(x_uint32_t _StatMode);

// Analog CXX : std_filesystem_is_directory
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_directory(x_uint32_t _StatMode);

// Analog CXX : std_filesystem_is_fifo
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_fifo(x_uint32_t _StatMode);

// Analog CXX : std_filesystem_is_other
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_other(x_uint32_t _StatMode);

// Analog CXX : std_filesystem_is_regular_file
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_regular_file(x_uint32_t _StatMode);

// Analog CXX : std_filesystem_is_socket
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_socket(x_uint32_t _StatMode);

// Analog CXX : std_filesystem_is_symlink
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_symlink(x_uint32_t _StatMode);

// FS: Copy a path to another path
_XPOSIXAPI_ int __xcall__ x_fs_path_copy(const char* _Source, const char* _Target);

// FS: Rename path
_XPOSIXAPI_ int __xcall__ x_fs_path_rename(const char* _OldPath, const char* _NewPath);



// FS: Copy file to another path
_XPOSIXAPI_ int __xcall__ x_fs_file_copy(const char* _Source, const char* _Target);

// FS: Copy directory to another path
_XPOSIXAPI_ int __xcall__ x_fs_dir_copy(const char* _Source, const char* _Target);



XCC_CXX_EXTERN_END

#endif

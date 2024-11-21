#include <xcc-posix/filesystem.h>
#include <xcc-posix/memory.h>
#include <xcc-posix/string.h>
#include <xcc-posix/system.h>
#if defined(XCC_SYSTEM_WINDOWS)
#include <io.h>
#else
#if defined(XCC_SYSTEM_LINUX)
#include <sys/vfs.h>
#endif
#if defined(XCC_SYSTEM_DARWIN)
#include <sys/param.h>
#include <sys/mount.h>
#endif
#include <dirent.h>
#include <errno.h>
#include <sys/statvfs.h>
#endif
#include <fcntl.h>
#include <stdarg.h>



// posix : dirname
_XPOSIXAPI_ char* __xcall__ x_posix_dirname(char* _FilePath)
{
	if(_FilePath == NULL)
	{
		return x_posix_strdup(".");
	}
	char*		path = _FilePath;
#if defined(XCC_SYSTEM_WINDOWS)
	while (_FilePath && *_FilePath != 0)
	{
		if(*_FilePath == '\\')
		{
			*_FilePath = '/';
		}
		++_FilePath;
	}
#endif

	// ---------- glibc ----------
	// static const char	dot[] = ".";
	char*			last_slash = NULL;

	/* Find last '/'.  */
	last_slash = path != NULL ? strrchr (path, '/') : NULL;

	if (last_slash != NULL && last_slash != path && last_slash[1] == '\0')
	{
		/* Determine whether all remaining characters are slashes.  */
		char *runp;

		for (runp = last_slash; runp != path; --runp)
			if (runp[-1] != '/')
				break;

		/* The '/' is the last character, we have to look further.  */
		if (runp != path)
			last_slash = x_posix_memrchr (path, '/', runp - path);
	}

	if (last_slash != NULL)
	{
		/* Determine whether all remaining characters are slashes.  */
		char *runp;

		for (runp = last_slash; runp != path; --runp)
			if (runp[-1] != '/')
				break;

		/* Terminate the path.  */
		if (runp == path)
		{
			/* The last slash is the first character in the string.  We have to
			   return "/".  As a special case we have to return "//" if there
			   are exactly two slashes at the beginning of the string.  See
			   XBD 4.10 Path Name Resolution for more information.  */
			if (last_slash == path + 1)
				++last_slash;
			else
				last_slash = path + 1;
		}
		else
			last_slash = runp;

		last_slash[0] = '\0';
	}
	else
		/* This assignment is ill-designed but the XPG specs require to
		   return a string containing "." in any case no directory part is
		   found and so a static and constant string is required.  */
		// path = (char *) dot;
		path = x_posix_strdup(".");

	return path;
}

// posix : basename
_XPOSIXAPI_ char* __xcall__ x_posix_basename(char* _FilePath)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_FilePath == NULL)
	{
		return NULL;
	}
#endif
	char*		vTail_Linux = (char*)x_posix_strrchr(_FilePath, L'/');
	char*		vTail_Win = (char*)x_posix_strrchr(_FilePath, L'\\');
	char*		vTail = vTail_Linux > vTail_Win ? vTail_Linux : vTail_Win;
	if(vTail)
	{
		return vTail + 1;
	}
	return _FilePath;
}





// posix : wdirname
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wdirname(wchar_t* _FilePath)
{
	if(_FilePath == NULL)
	{
		return x_posix_wcsdup(L".");
	}
	wchar_t*		path = _FilePath;
#if defined(XCC_SYSTEM_WINDOWS)
	while (_FilePath && *_FilePath != 0)
	{
		if(*_FilePath == L'\\')
		{
			*_FilePath = L'/';
		}
		++_FilePath;
	}
#endif

	// ---------- glibc ----------
	// static const char	dot[] = ".";
	wchar_t*		last_slash = NULL;

	/* Find last '/'.  */
	last_slash = path != NULL ? wcsrchr (path, L'/') : NULL;

	if (last_slash != NULL && last_slash != path && last_slash[1] == L'\0')
	{
		/* Determine whether all remaining characters are slashes.  */
		wchar_t *runp;

		for (runp = last_slash; runp != path; --runp)
			if (runp[-1] != L'/')
				break;

		/* The '/' is the last character, we have to look further.  */
		if (runp != path)
			last_slash = x_posix_memrchr (path, L'/', runp - path);
	}

	if (last_slash != NULL)
	{
		/* Determine whether all remaining characters are slashes.  */
		wchar_t *runp;

		for (runp = last_slash; runp != path; --runp)
			if (runp[-1] != L'/')
				break;

		/* Terminate the path.  */
		if (runp == path)
		{
			/* The last slash is the first character in the string.  We have to
			   return "/".  As a special case we have to return "//" if there
			   are exactly two slashes at the beginning of the string.  See
			   XBD 4.10 Path Name Resolution for more information.  */
			if (last_slash == path + 1)
				++last_slash;
			else
				last_slash = path + 1;
		}
		else
			last_slash = runp;

		last_slash[0] = L'\0';
	}
	else
		/* This assignment is ill-designed but the XPG specs require to
		   return a string containing "." in any case no directory part is
		   found and so a static and constant string is required.  */
		// path = (char *) dot;
		path = x_posix_wcsdup(L".");

	return path;
}

// posix : wbasename
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wbasename(wchar_t* _FilePath)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_FilePath == NULL)
	{
		return NULL;
	}
#endif
	wchar_t*	vTail_Linux = (wchar_t*)x_posix_wcsrchr(_FilePath, L'/');
	wchar_t*	vTail_Win = (wchar_t*)x_posix_wcsrchr(_FilePath, L'\\');
	wchar_t*	vTail = vTail_Linux > vTail_Win ? vTail_Linux : vTail_Win;
	if(vTail)
	{
		return vTail + 1;
	}
	return _FilePath;
}





// posix : dup
_XPOSIXAPI_ int __xcall__ x_posix_dup(int _FileHandle)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _dup(_FileHandle);
#else
	return dup(_FileHandle);
#endif
}

// posix : dup2
_XPOSIXAPI_ int __xcall__ x_posix_dup2(int _FileHandleSrc, int _FileHandleDst)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _dup2(_FileHandleSrc, _FileHandleDst);
#else
	return dup2(_FileHandleSrc, _FileHandleDst);
#endif
}

// posix : open
_XPOSIXAPI_ int __xcall__ x_posix_open(const char* _Filename, int _Flag, ...)
{
	int		vMode = 0;
	if (_Flag & O_CREAT)
	{
		va_list		vArg;
		va_start (vArg, _Flag);
		vMode = va_arg (vArg, int);
		va_end (vArg);
	}

#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vFilenameW = x_posix_strutow(_Filename);
	int 		vStatus = EINVAL;

	if(vFilenameW)
	{
		vStatus = _wopen(vFilenameW, _Flag, vMode);
	}
	if(vFilenameW)
	{
		x_posix_free(vFilenameW);
	}
	return vStatus;
#else
	return open(_Filename, _Flag, vMode);
#endif
}

// posix : lseek
_XPOSIXAPI_ off_t __xcall__ x_posix_lseek(int _FileHandle, off_t _Offset, int _Origin)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _lseek(_FileHandle, _Offset, _Origin);
#else
	return lseek(_FileHandle, _Offset, _Origin);
#endif
}

// posix : read
_XPOSIXAPI_ ssize_t __xcall__ x_posix_read(int _FileHandle, void* _Buffer, size_t _Count)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _read(_FileHandle, _Buffer, (uint32_t)_Count);
#else
	return read(_FileHandle, _Buffer, _Count);
#endif
}

// posix : write
_XPOSIXAPI_ ssize_t __xcall__ x_posix_write(int _FileHandle, const void* _Buffer, size_t _Count)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _write(_FileHandle, _Buffer, (uint32_t)_Count);
#else
	return write(_FileHandle, _Buffer, _Count);
#endif
}

// posix : close
_XPOSIXAPI_ int __xcall__ x_posix_close(int _FileHandle)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _close(_FileHandle);
#else
	return close(_FileHandle);
#endif
}

// posix : sync
_XPOSIXAPI_ void __xcall__ x_posix_sync(void)
{
#if !defined(XCC_SYSTEM_WINDOWS)
	return sync();
#endif
}



// posix : access
_XPOSIXAPI_ int __xcall__ x_posix_access(const char* _Path, int _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vPathW = x_posix_strutow(_Path);
	int 		vStatus = EINVAL;

	if(vPathW)
	{
		vStatus = _waccess(vPathW, _Mode);
	}
	if(vPathW)
	{
		x_posix_free(vPathW);
	}
	return vStatus;
#else
	return access(_Path, _Mode);
#endif
}

// posix : mkdir
_XPOSIXAPI_ int __xcall__ x_posix_mkdir(const char* _Directory, mode_t _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	XCC_UNUSED(_Mode);
	wchar_t*	vDirectoryW = x_posix_strutow(_Directory);
	int 		vStatus = EINVAL;

	if(vDirectoryW)
	{
		vStatus = _wmkdir(vDirectoryW);
	}
	if(vDirectoryW)
	{
		x_posix_free(vDirectoryW);
	}
	return vStatus;
#else
	return mkdir(_Directory, _Mode);
#endif
}

// posix : mkdir_r
_XPOSIXAPI_ int __xcall__ x_posix_mkdir_r(const char* _Directory, mode_t _Mode)
{
	int 		vStatus = 0;
	char*		vDirname = NULL;
	if(_Directory == NULL)
	{
		return x_posix_seterrno(EINVAL);
	}

	if(0 != x_posix_access(_Directory, F_OK))
	{
		vDirname = x_posix_dirname(x_posix_strdup(_Directory));
		if(vDirname)
		{
			vStatus = x_posix_mkdir_r(vDirname, _Mode);
			if(0 == vStatus)
			{
				vStatus = x_posix_mkdir(_Directory, _Mode);
			}
			x_posix_free(vDirname);
		}
		else
		{
			vStatus = x_posix_seterrno(EINVAL);
		}
	}
	return vStatus;
}

// posix : chmod
_XPOSIXAPI_ int __xcall__ x_posix_chmod(const char* _Path, int _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vFilenameW = x_posix_strutow(_Path);
	int 		vStatus = EINVAL;

	if(vFilenameW)
	{
		vStatus = _wchmod(vFilenameW, _Mode);
	}
	if(vFilenameW)
	{
		x_posix_free(vFilenameW);
	}
	return vStatus;
#else
	return chmod(_Path, _Mode);
#endif
}

// posix : rmdir
_XPOSIXAPI_ int __xcall__ x_posix_rmdir(const char* _Path)
{
#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vFilenameW = x_posix_strutow(_Path);
	int 		vStatus = EINVAL;

	if(vFilenameW)
	{
		vStatus = _wrmdir(vFilenameW);
	}
	if(vFilenameW)
	{
		x_posix_free(vFilenameW);
	}
	return vStatus;
#else
	return rmdir(_Path);
#endif
}

// posix : rmdir_r
_XPOSIXAPI_ int __xcall__ x_posix_rmdir_r(const char* _Path)
{
	int 			vStatus = 0;
	x_fs_find_t		vStream = NULL;
	x_file_data_t		vFileData;
	char 			vFindPathR[X_FS_MAX_PATH];
	if(_Path == NULL)
	{
		return x_posix_seterrno(EINVAL);
	}

	if(0 != x_posix_access(_Path, F_OK))
	{
		return x_posix_seterrno(0);
	}

	vStream = x_fs_find_first(_Path, &vFileData);
	if(vStream == NULL)
	{
		return x_posix_seterrno(EIO);
	}
	do
	{
		if(0 == x_posix_strcmp(vFileData.name, ".") || 0 == x_posix_strcmp(vFileData.name, ".."))
		{
			continue;
		}
		sprintf(vFindPathR, "%s/%s", _Path, vFileData.name);
		if(x_fs_path_is_directory(vFileData.mode))
		{
			vStatus = x_posix_rmdir_r(vFindPathR);
		}
		else
		{
			vStatus = x_posix_remove(vFindPathR);
		}
	} while (0 == x_fs_find_next(vStream, &vFileData) && 0 == vStatus);
	x_fs_find_close(vStream);

	return x_posix_rmdir(_Path);
}

// posix : remove
_XPOSIXAPI_ int __xcall__ x_posix_remove(const char* _FileName)
{
#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vFilenameW = x_posix_strutow(_FileName);
	int 		vStatus = EINVAL;

	if(vFilenameW)
	{
		vStatus = _wremove(vFilenameW);
	}
	if(vFilenameW)
	{
		x_posix_free(vFilenameW);
	}
	return vStatus;
#else
	return remove(_FileName);
#endif
}

// posix : rename
_XPOSIXAPI_ int __xcall__ x_posix_rename(const char* _OldFileName, const char* _NewFileName)
{
#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vOldFileNameW = x_posix_strutow(_OldFileName);
	wchar_t*	vNewFileNameW = x_posix_strutow(_NewFileName);
	int 		vStatus = EINVAL;

	if(vOldFileNameW && vNewFileNameW)
	{
		vStatus = _wrename(vOldFileNameW, vNewFileNameW);
	}
	if(vOldFileNameW)
	{
		x_posix_free(vOldFileNameW);
	}
	if(vNewFileNameW)
	{
		x_posix_free(vNewFileNameW);
	}
	return vStatus;
#else
	return rename(_OldFileName, _NewFileName);
#endif
}

// posix : unlink
_XPOSIXAPI_ int __xcall__ x_posix_unlink(const char* _FileName)
{
#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vFilenameW = x_posix_strutow(_FileName);
	int 		vStatus = EINVAL;

	if(vFilenameW)
	{
		vStatus = _wunlink(vFilenameW);
	}
	if(vFilenameW)
	{
		x_posix_free(vFilenameW);
	}
	return vStatus;
#else
	return unlink(_FileName);
#endif
}

// posix : tmpfile
_XPOSIXAPI_ FILE* __xcall__ x_posix_tmpfile(void)
{
	return tmpfile();
}

// posix : truncate
_XPOSIXAPI_ int __xcall__ x_posix_truncate(const char* _Filename, x_int64_t _Size)
{
#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vFilenameW = x_posix_strutow(_Filename);
	int 		vStatus = EINVAL;
	HANDLE		vHandle = INVALID_HANDLE_VALUE;
	LARGE_INTEGER	vFileSize;

	if(vFilenameW)
	{
		vHandle = CreateFileW(vFilenameW, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(INVALID_HANDLE_VALUE != vHandle)
		{
			vFileSize.QuadPart = _Size;
			if(SetFilePointerEx(vHandle, vFileSize, NULL, FILE_BEGIN))
			{
				if(SetEndOfFile(vHandle))
				{
					vStatus = 0;
				}
			}
			CloseHandle(vHandle);
		}
	}
	if(vFilenameW)
	{
		x_posix_free(vFilenameW);
	}
	return vStatus;
#else
	if(0 != access(_Filename, F_OK))
	{
		FILE*		vHandle = fopen(_Filename, "ab+");
		char		vSpaceByte[1];
		x_posix_memset(vSpaceByte, 0, 1);
		if(vHandle)
		{
			fwrite(vSpaceByte, 1, 1, vHandle);
			fflush(vHandle);
			fclose(vHandle);
		}
	}
	return truncate(_Filename, _Size);
#endif
}



// posix : waccess
_XPOSIXAPI_ int __xcall__ x_posix_waccess(const wchar_t* _Path, int _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _waccess(_Path, _Mode);
#else
	char*		vPathU = x_posix_strwtou(_Path);
	int 		vStatus = EINVAL;

	if(vPathU)
	{
		vStatus = access(vPathU, _Mode);
	}
	if(vPathU)
	{
		x_posix_free(vPathU);
	}
	return vStatus;
#endif
}

// posix : wmkdir
_XPOSIXAPI_ int __xcall__ x_posix_wmkdir(const wchar_t* _Directory, mode_t _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	XCC_UNUSED(_Mode);
	return _wmkdir(_Directory);
#else
	char*		vDirectoryU = x_posix_strwtou(_Directory);
	int 		vStatus = EINVAL;

	if(vDirectoryU)
	{
		vStatus = mkdir(vDirectoryU, _Mode);
	}
	if(vDirectoryU)
	{
		x_posix_free(vDirectoryU);
	}
	return vStatus;
#endif
}

// posix : wmkdir_r
_XPOSIXAPI_ int __xcall__ x_posix_wmkdir_r(const wchar_t* _Directory, mode_t _Mode)
{
	int 		vStatus = 0;
	wchar_t*	vDirname = NULL;
	if(_Directory == NULL)
	{
		return x_posix_seterrno(EINVAL);
	}

	if(0 != x_posix_waccess(_Directory, F_OK))
	{
		vDirname = x_posix_wdirname(x_posix_wcsdup(_Directory));
		if(vDirname)
		{
			vStatus = x_posix_wmkdir_r(vDirname, _Mode);
			if(0 == vStatus)
			{
				vStatus = x_posix_wmkdir(_Directory, _Mode);
			}
			x_posix_free(vDirname);
		}
		else
		{
			vStatus = x_posix_seterrno(EINVAL);
		}
	}
	return vStatus;
}

// posix : wchmod
_XPOSIXAPI_ int __xcall__ x_posix_wchmod(const wchar_t* _Path, int _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _wchmod(_Path, _Mode);
#else
	char*		vFilenameU = x_posix_strwtou(_Path);
	int 		vStatus = EINVAL;

	if(vFilenameU)
	{
		vStatus = chmod(vFilenameU, _Mode);
	}
	if(vFilenameU)
	{
		x_posix_free(vFilenameU);
	}
	return vStatus;
#endif
}

// posix : wrmdir
_XPOSIXAPI_ int __xcall__ x_posix_wrmdir(const wchar_t* _Path)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _wrmdir(_Path);
#else
	char*		vFilenameU = x_posix_strwtou(_Path);
	int 		vStatus = EINVAL;

	if(vFilenameU)
	{
		vStatus = rmdir(vFilenameU);
	}
	if(vFilenameU)
	{
		x_posix_free(vFilenameU);
	}
	return vStatus;
#endif
}

// posix : wrmdir_r
_XPOSIXAPI_ int __xcall__ x_posix_wrmdir_r(const wchar_t* _Path)
{
	int 			vStatus = 0;
	char*			vPathU = x_posix_strwtou(_Path);
	if(vPathU)
	{
		vStatus = x_posix_rmdir(vPathU);
	}
	if(vPathU)
	{
		x_posix_free(vPathU);
	}
	return vStatus;
}

// posix : wremove
_XPOSIXAPI_ int __xcall__ x_posix_wremove(const wchar_t* _FileName)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _wremove(_FileName);
#else
	char*		vFilenameU = x_posix_strwtou(_FileName);
	int 		vStatus = EINVAL;

	if(vFilenameU)
	{
		vStatus = remove(vFilenameU);
	}
	if(vFilenameU)
	{
		x_posix_free(vFilenameU);
	}
	return vStatus;
#endif
}

// posix : wrename
_XPOSIXAPI_ int __xcall__ x_posix_wrename(const wchar_t* _OldFileName, const wchar_t* _NewFileName)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _wrename(_OldFileName, _NewFileName);
#else
	char*		vOldFileNameU = x_posix_strwtou(_OldFileName);
	char*		vNewFileNameU = x_posix_strwtou(_NewFileName);
	int 		vStatus = EINVAL;

	if(vOldFileNameU && vNewFileNameU)
	{
		vStatus = rename(vOldFileNameU, vNewFileNameU);
	}
	if(vOldFileNameU)
	{
		x_posix_free(vOldFileNameU);
	}
	if(vNewFileNameU)
	{
		x_posix_free(vNewFileNameU);
	}
	return vStatus;
#endif
}

// posix : wunlink
_XPOSIXAPI_ int __xcall__ x_posix_wunlink(const wchar_t* _FileName)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _wunlink(_FileName);
#else
	char*		vFilenameU = x_posix_strwtou(_FileName);
	int 		vStatus = EINVAL;

	if(vFilenameU)
	{
		vStatus = unlink(vFilenameU);
	}
	if(vFilenameU)
	{
		x_posix_free(vFilenameU);
	}
	return vStatus;
#endif
}



// posix : fopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_fopen(const char* _Filename, const char* _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vFilenameW = x_posix_strutow(_Filename);
	wchar_t*	vModeW = x_posix_strutow(_Mode);
	FILE*		vHandle = NULL;

	if(vFilenameW && vModeW)
	{
		_wfopen_s(&vHandle, vFilenameW, vModeW);
	}
	if(vFilenameW)
	{
		x_posix_free(vFilenameW);
	}
	if(vModeW)
	{
		x_posix_free(vModeW);
	}
	return vHandle;
#else
	return fopen(_Filename, _Mode);
#endif
}

// posix : fdopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_fdopen(int _Fildes, const char* _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _fdopen(_Fildes, _Mode);
#else
	return fdopen(_Fildes, _Mode);
#endif
}

// posix : freopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_freopen(const char* _Filename, const char* _Mode, FILE* _Stream)
{
#if defined(XCC_SYSTEM_WINDOWS)
	wchar_t*	vFilenameW = x_posix_strutow(_Filename);
	wchar_t*	vModeW = x_posix_strutow(_Mode);
	FILE*		vHandle = NULL;

	if(vFilenameW && vModeW)
	{
		_wfreopen_s(&vHandle, vFilenameW, vModeW, _Stream);
	}
	if(vFilenameW)
	{
		x_posix_free(vFilenameW);
	}
	if(vModeW)
	{
		x_posix_free(vModeW);
	}
	return vHandle;
#else
	return freopen(_Filename, _Mode, _Stream);
#endif
}



// posix : wfopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_wfopen(const wchar_t* _Filename, const wchar_t* _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	FILE*		vHandle = NULL;
	_wfopen_s(&vHandle, _Filename, _Mode);
	return vHandle;
#else
	char*		vFilenameU = x_posix_strwtou(_Filename);
	char*		vModeU = x_posix_strwtou(_Mode);
	FILE*		vHandle = NULL;

	if(vFilenameU && vModeU)
	{
		vHandle = fopen(vFilenameU, vModeU);
	}
	if(vFilenameU)
	{
		x_posix_free(vFilenameU);
	}
	if(vModeU)
	{
		x_posix_free(vModeU);
	}
	return vHandle;
#endif
}

// posix : wfdopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_wfdopen(int _Fildes, const wchar_t* _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _wfdopen(_Fildes, _Mode);
#else
	char*		vModeU = x_posix_strwtou(_Mode);
	FILE*		vHandle = NULL;

	if(vModeU)
	{
		vHandle = fdopen(_Fildes, vModeU);
	}
	if(vModeU)
	{
		x_posix_free(vModeU);
	}
	return vHandle;
#endif
}

// posix : wfreopen
_XPOSIXAPI_ FILE* __xcall__ x_posix_wfreopen(const wchar_t* _Filename, const wchar_t* _Mode, FILE* _Stream)
{
#if defined(XCC_SYSTEM_WINDOWS)
	FILE*		vHandle = NULL;
	_wfreopen_s(&vHandle, _Filename, _Mode, _Stream);
	return vHandle;
#else
	char*		vFilenameU = x_posix_strwtou(_Filename);
	char*		vModeU = x_posix_strwtou(_Mode);
	FILE*		vHandle = NULL;

	if(vFilenameU && vModeU)
	{
		vHandle = freopen(vFilenameU, vModeU, _Stream);
	}
	if(vFilenameU)
	{
		x_posix_free(vFilenameU);
	}
	if(vModeU)
	{
		x_posix_free(vModeU);
	}
	return vHandle;
#endif
}



// posix : fileno
_XPOSIXAPI_ int __xcall__ x_posix_fileno(FILE* _Stream)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _fileno(_Stream);
#else
	return fileno(_Stream);
#endif
}

// posix : fseek
_XPOSIXAPI_ int __xcall__ x_posix_fseek(FILE* _Stream, long _Offset, int _Whence)
{
	return fseek(_Stream, _Offset, _Whence);
}

// posix : fseek64
_XPOSIXAPI_ int64_t __xcall__ x_posix_fseek64(FILE* _Stream, int64_t _Offset, int _Whence)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _fseeki64(_Stream, _Offset, _Whence);
#elif defined(XCC_SYSTEM_ANDROID)
	return fseek(_Stream, _Offset, _Whence);
#else
	return fseeko(_Stream, _Offset, _Whence);
#endif
}

// posix : ftell
_XPOSIXAPI_ long __xcall__ x_posix_ftell(FILE* _Stream)
{
	return ftell(_Stream);
}

// posix : ftell64
_XPOSIXAPI_ int64_t __xcall__ x_posix_ftell64(FILE* _Stream)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return _ftelli64(_Stream);
#elif defined(XCC_SYSTEM_ANDROID)
	return ftell(_Stream);
#else
	return ftello(_Stream);
#endif
}

// posix : rewind
_XPOSIXAPI_ void __xcall__ x_posix_rewind(FILE* _Stream)
{
	rewind(_Stream);
}

// posix : fgetc
_XPOSIXAPI_ int __xcall__ x_posix_fgetc(FILE* _Stream)
{
	return fgetc(_Stream);
}

// posix : fputc
_XPOSIXAPI_ int __xcall__ x_posix_fputc(int _Character, FILE* _Stream)
{
	return fputc(_Character, _Stream);
}

// posix : fgets
_XPOSIXAPI_ char* __xcall__ x_posix_fgets(char* _Buffer, int _MaxCount, FILE* _Stream)
{
	return fgets(_Buffer, _MaxCount, _Stream);
}

// posix : fputs
_XPOSIXAPI_ int __xcall__ x_posix_fputs(const char* _Buffer, FILE* _Stream)
{
	return fputs(_Buffer, _Stream);
}

// posix : fread
_XPOSIXAPI_ size_t __xcall__ x_posix_fread(void* _Memory, size_t _Size, size_t _Item, FILE* _Stream)
{
	return fread(_Memory, _Size, _Item, _Stream);
}

// posix : fwrite
_XPOSIXAPI_ size_t __xcall__ x_posix_fwrite(const void* _Memory, size_t _Size, size_t _Item, FILE* _Stream)
{
	return fwrite(_Memory, _Size, _Item, _Stream);
}

// posix : feof
_XPOSIXAPI_ int __xcall__ x_posix_feof(FILE* _Stream)
{
	return feof(_Stream);
}

// posix : ferror
_XPOSIXAPI_ int __xcall__ x_posix_ferror(FILE* _Stream)
{
	return ferror(_Stream);
}

// posix : fsync
_XPOSIXAPI_ int __xcall__ x_posix_fsync(int _Fildes)
{
#if defined(XCC_SYSTEM_WINDOWS)
	XCC_UNUSED(_Fildes);
	return 0;
#else
	return fsync(_Fildes);
#endif
}

// posix : fclose
_XPOSIXAPI_ int __xcall__ x_posix_fclose(FILE* _Stream)
{
	return fclose(_Stream);
}

// posix : fsize
_XPOSIXAPI_ unsigned long long __xcall__ x_posix_fsize(const char* _Filename)
{
	x_file_stat_t 		vStat;
	if(0 == x_fs_path_stat(_Filename, &vStat))
	{
		return vStat.st_size;
	}
	return 0;
}



// posix : opendir
_XPOSIXAPI_ DIR* __xcall__ x_posix_opendir(const char* _Name)
{
	if(_Name == NULL)
	{
		return NULL;
	}
#if defined(XCC_COMPILER_MSVC)
	wchar_t 		vFindPath[X_FS_MAX_PATH] = {0};
	wchar_t*		vDirectoryPath = x_posix_strutow(_Name);
	DIR*			vStream = (DIR*)x_posix_malloc(sizeof(DIR));
	struct _wfinddata64_t*	vFileInfo = (struct _wfinddata64_t*)x_posix_malloc(sizeof(struct _wfinddata64_t));
	intptr_t 		vHandle = 0;

	if(vDirectoryPath && vStream && vFileInfo && x_posix_wcslen(vDirectoryPath) < (X_FS_MAX_PATH - 5))
	{
		x_posix_memset(vStream, 0, sizeof(DIR));
		x_posix_memset(vFileInfo, 0, sizeof(struct _wfinddata64_t));
		x_posix_wcscpy(vFindPath, vDirectoryPath);
		x_posix_wcscat(vFindPath, L"/*.*");

		vHandle = _wfindfirst64(vFindPath, vFileInfo);
		if(vHandle)
		{
			vStream->__fd = (void*)vHandle;
			vStream->__finddata64 = vFileInfo;
			vStream->__directory = x_posix_strdup(_Name);

			x_posix_free(vDirectoryPath);
			return vStream;
		}
	}

	x_posix_free(vDirectoryPath);
	_findclose(vHandle);
	x_posix_free(vFileInfo);
	x_posix_free(vStream);
	return NULL;
#else
	return opendir(_Name);
#endif
}

// posix : readdir
_XPOSIXAPI_ struct dirent* __xcall__ x_posix_readdir(DIR* _Stream)
{
#if defined(XCC_COMPILER_MSVC)
	struct _wfinddata64_t*	vFileInfo = NULL;
	struct dirent*		vDirent = NULL;
	char*			vFileName = NULL;
	struct _stat64		vFileStat;
	char 			vFullPath[X_FS_MAX_PATH] = {0};
	int 			vSync = 0;
	if(_Stream == NULL)
	{
		return NULL;
	}

	// read local data
	if(_Stream->__finddata64)
	{
		vFileInfo = _Stream->__finddata64;
		_Stream->__finddata64 = NULL;
	}
	else
	{
		vFileInfo = (struct _wfinddata64_t*)x_posix_malloc(sizeof(struct _wfinddata64_t));
		if(vFileInfo == NULL)
		{
			return NULL;
		}
		x_posix_memset(vFileInfo, 0, sizeof(struct _wfinddata64_t));

		vSync = _wfindnext64((intptr_t)(_Stream->__fd), vFileInfo);
		if(vSync != 0)
		{
			x_posix_free(vFileInfo);
			return NULL;
		}
	}

	// convert file name
	vFileName = x_posix_strwtou(vFileInfo->name);
	if(vFileName == NULL)
	{
		x_posix_free(vFileInfo);
		return NULL;
	}
	if(x_posix_strlen(vFileName) >= MAX_PATH)
	{
		x_posix_free(vFileName);
		x_posix_free(vFileInfo);
		return NULL;
	}

	// build a new item
	if(_Stream->__dirent)
	{
		x_posix_free(_Stream->__dirent);
		_Stream->__dirent = NULL;
	}
	vDirent = (struct dirent*)x_posix_malloc(sizeof(struct dirent));
	if(vDirent == NULL)
	{
		x_posix_free(vFileName);
		x_posix_free(vFileInfo);
		return NULL;
	}
	x_posix_memset(vDirent, 0, sizeof(struct dirent));
	_Stream->__dirent = vDirent;

	// convert structure
	x_posix_strcpy(vFullPath, _Stream->__directory);
	x_posix_strcat(vFullPath, "/");
	x_posix_strcat(vFullPath, vFileName);
	x_fs_path_stat(vFullPath, &vFileStat);

	vDirent->d_ino = vFileStat.st_ino;
	vDirent->d_type = (unsigned char)vFileStat.st_mode;
	x_posix_strcpy(vDirent->d_name, vFileName);
	vDirent->d_reclen = (unsigned short)x_posix_strlen(vDirent->d_name);

	x_posix_free(vFileName);
	return vDirent;
#else
	return readdir(_Stream);
#endif
}

// posix : closedir
_XPOSIXAPI_ int __xcall__ x_posix_closedir(DIR* _Stream)
{
#if defined(XCC_COMPILER_MSVC)
	if(_Stream == NULL)
	{
		return -1;
	}
	x_posix_free(_Stream->__directory);
	x_posix_free(_Stream->__finddata64);
	x_posix_free(_Stream->__dirent);
	x_posix_free(_Stream);
	return 0;
#else
	return closedir(_Stream);
#endif
}



// FS: Convert path to common format
_XPOSIXAPI_ char* __xcall__ x_fs_path_to_common(const char* _SrcPath)
{
	char*		vConvertPath = x_posix_strdup(_SrcPath);
	x_size_t 	vLength = x_posix_strlen(vConvertPath);
	if(vLength)
	{
		for(x_size_t vIndex = 0; vIndex < vLength; ++vIndex)
		{
			if(vConvertPath[vIndex] == '\\')
			{
				vConvertPath[vIndex] = '/';
			}
		}
		while(vLength > 1 && vConvertPath[vLength - 1] == '/')
		{
			vConvertPath[vLength - 1] = '\0';
			vLength -= 1;
		}
	}
	return vConvertPath;
}

// FS: Convert path to native format
_XPOSIXAPI_ char* __xcall__ x_fs_path_to_native(const char* _SrcPath)
{
	char*		vConvertPath = x_posix_strdup(_SrcPath);
	x_size_t 	vLength = x_posix_strlen(vConvertPath);
	if(vLength)
	{
		for(x_size_t vIndex = 0; vIndex < vLength; ++vIndex)
		{
			if(vConvertPath[vIndex] == '/')
			{
				vConvertPath[vIndex] = '\\';
			}
		}
		while(vLength > 1 && vConvertPath[vLength - 1] == '\\')
		{
			vConvertPath[vLength - 1] = '\0';
			vLength -= 1;
		}
	}
	return vConvertPath;
}

// FS: Find the last delimiter
_XPOSIXAPI_ const char* __xcall__ x_fs_path_find_last_div(const char* _FilePath)
{
	if(_FilePath == NULL)
	{
		return NULL;
	}

	const char*	vTail_Linux = x_posix_strrchr(_FilePath, '/');
	const char*	vTail_Win = x_posix_strrchr(_FilePath, '\\');
	if(vTail_Linux && vTail_Win)
	{
		if(vTail_Win - vTail_Linux > 0)
		{
			return vTail_Win;
		}
		else
		{
			return vTail_Linux;
		}
	}
	else if(vTail_Linux)
	{
		return vTail_Linux;
	}
	else if(vTail_Win)
	{
		return vTail_Win;
	}
	return NULL;
}



// FS: Query the space information of the specified partition
_XPOSIXAPI_ int __xcall__ x_fs_disk_space(const char* _Path, x_fs_space_t* _Space)
{
	if(_Path == NULL || x_posix_strlen(_Path) < 1 || _Space == NULL)
	{
		return EINVAL;
	}

	x_posix_memset(_Space, 0, sizeof(x_fs_space_t));
#if defined(XCC_SYSTEM_WINDOWS)
	char 			vDrive[3] = {_Path[0], ':', 0};
	ULARGE_INTEGER		vAvailable;
	ULARGE_INTEGER		vTotalBytes;
	ULARGE_INTEGER		vFreeBytes;
	if(!GetDiskFreeSpaceExA(vDrive, &vAvailable, &vTotalBytes, &vFreeBytes))
	{
		return EIO;
	}
	_Space->avail_bytes = vAvailable.QuadPart;
	_Space->free_bytes = vFreeBytes.QuadPart;
	_Space->total_bytes = vTotalBytes.QuadPart;
	return 0;
#else
	struct statfs		vDiskStatfs;
	int			vError = statfs(_Path, &vDiskStatfs);

	uint64_t		vBlockSize = vDiskStatfs.f_bsize;
	uint64_t		vAvailBlock = vDiskStatfs.f_bavail;
	uint64_t		vFreeBlock = vDiskStatfs.f_bfree;
	uint64_t		vTotalBlock = vDiskStatfs.f_blocks;

	_Space->avail_bytes = vAvailBlock * vBlockSize;
	_Space->free_bytes = vFreeBlock * vBlockSize;
	_Space->total_bytes = vTotalBlock * vBlockSize;
	return vError;
#endif
}



// FS: Open the specified directory and return to the first child node
_XPOSIXAPI_ x_fs_find_t __xcall__ x_fs_find_first(const char* _Directory, x_file_data_t* _FileData)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_Directory == NULL || _FileData == NULL)
	{
		return NULL;
	}
#endif

	// Necessary data construction
	x_file_stat_t	vFileStat;
	x_fs_find_t	vStream = (x_fs_find_t)x_posix_malloc(sizeof(struct x_fs_find_data));
	if(vStream == NULL)
	{
		return NULL;
	}
	x_posix_memset(vStream, 0, sizeof(struct x_fs_find_data));
#if defined(XCC_SYSTEM_WINDOWS)
	char* 			vFormat = x_fs_path_to_common(_Directory);
	uint64_t 		vLength = x_posix_strlen(vFormat);
	char 			vFindPath[X_FS_MAX_PATH];
	if(vFormat == NULL || (vLength == 0) || (vLength >= (X_FS_MAX_PATH - X_FS_MAX_NAME)))
	{
		x_posix_free(vStream);
		x_posix_free(vFormat);
		return NULL;
	}
	x_posix_strcpy(vStream->dir, vFormat);
	x_posix_strcpy(vFindPath, vFormat);
	x_posix_strcat(vFindPath, "/*.*");
	x_posix_free(vFormat);

	struct __finddata64_t	vFileInfo;
	intptr_t 		vHandle = _findfirst64(vFindPath, &vFileInfo);
	if(vHandle == -1L)
	{
		x_posix_free(vStream);
		return NULL;
	}
	const char*		vFileName = vFileInfo.name;
#else
	DIR* 			vHandle = opendir(_Directory);
	if(vHandle == NULL)
	{
		x_posix_free(vStream);
		return NULL;
	}
	struct dirent*		vDirEntry = readdir(vHandle);
	if(vDirEntry == NULL)
	{
		x_posix_free(vStream);
		closedir(vHandle);
		return NULL;
	}
	x_posix_strcpy(vStream->dir, _Directory);
	const char*		vFileName = vDirEntry->d_name;
#endif
	// Build file information
	vStream->handle = vHandle;
	x_posix_strcpy(_FileData->dir, vStream->dir);
	x_posix_strcpy(_FileData->path, vStream->dir);
	x_posix_strcat(_FileData->path, "/");
	x_posix_strcat(_FileData->path, vFileName);
	x_posix_strcpy(_FileData->name, vFileName);
	x_fs_path_stat(_FileData->path, &vFileStat);
	_FileData->size = vFileStat.st_size;
	_FileData->mode = vFileStat.st_mode;
	_FileData->atime = vFileStat.st_atime;
	_FileData->mtime = vFileStat.st_mtime;
	_FileData->ctime = vFileStat.st_ctime;

	return vStream;
}

// FS: Find the next name. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int __xcall__ x_fs_find_next(x_fs_find_t _Stream, x_file_data_t* _FileData)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_Stream == NULL || _FileData == NULL)
	{
		return x_posix_seterrno(EINVAL);
	}
#endif

	x_file_stat_t	vFileStat;
#if defined(XCC_SYSTEM_WINDOWS)
	struct __finddata64_t	vFileInfo;
	int 			vSync = _findnext64((intptr_t)(_Stream->handle), &vFileInfo);
	if(vSync != 0)
	{
		return vSync;
	}
	const char*		vFileName = vFileInfo.name;
#else
	struct dirent*		vDirEntry = readdir((DIR*)(_Stream->handle));
	if(vDirEntry == NULL)
	{
		return x_posix_errno();
	}
	const char*		vFileName = vDirEntry->d_name;
#endif
	// Build file information
	x_posix_strcpy(_FileData->dir, _Stream->dir);
	x_posix_strcpy(_FileData->path, _Stream->dir);
	x_posix_strcat(_FileData->path, "/");
	x_posix_strcat(_FileData->path, vFileName);
	x_posix_strcpy(_FileData->name, vFileName);
	x_fs_path_stat(_FileData->path, &vFileStat);
	_FileData->size = vFileStat.st_size;
	_FileData->mode = vFileStat.st_mode;
	_FileData->atime = vFileStat.st_atime;
	_FileData->mtime = vFileStat.st_mtime;
	_FileData->ctime = vFileStat.st_ctime;
	return 0;
}

// FS: This function closes the specified search handle. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int __xcall__ x_fs_find_close(x_fs_find_t _Stream)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_Stream == NULL)
	{
		return x_posix_seterrno(EINVAL);
	}
#endif

#if defined(XCC_SYSTEM_WINDOWS)
	int 		vError = _findclose((intptr_t)(_Stream->handle));
#else
	int 		vError = closedir((DIR*)(_Stream->handle));
#endif
	x_posix_free(_Stream);
	return vError;
}



// FS: Does the path exist
_XPOSIXAPI_ bool __xcall__ x_fs_path_exists(const char* _FilePath)
{
	return 0 == x_posix_access(_FilePath, F_OK);
}

// Gets information about the file the path points to
_XPOSIXAPI_ int __xcall__ x_fs_path_stat(const char* _FilePath, x_file_stat_t* _Stat)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_FilePath == NULL || _Stat == NULL)
	{
		return x_posix_seterrno(EINVAL);
	}
#endif
#if defined(XCC_SYSTEM_WINDOWS)
	int 		vSync = -1;
	wchar_t*	vFilePathW = x_posix_strutow(_FilePath);
	if(vFilePathW)
	{
		vSync = _wstat64(vFilePathW, _Stat);
		x_posix_free(vFilePathW);
	}
	return vSync;
#else
	return stat(_FilePath, _Stat);
#endif
}

// Analog CXX : std_filesystem_is_block_file
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_block_file(x_uint32_t _StatMode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	UNREFERENCED_PARAMETER(_StatMode);
	return false;
#else
	return S_ISBLK(_StatMode);
#endif
}

// Analog CXX : std_filesystem_is_character_file
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_character_file(x_uint32_t _StatMode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return (_StatMode & S_IFMT) == _S_IFCHR;
#else
	return S_ISCHR(_StatMode);
#endif
}

// Analog CXX : std_filesystem_is_directory
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_directory(x_uint32_t _StatMode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return (_StatMode & S_IFMT) == _S_IFDIR;
#else
	return S_ISDIR(_StatMode);
#endif
}

// Analog CXX : std_filesystem_is_fifo
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_fifo(x_uint32_t _StatMode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return (_StatMode & S_IFMT) == _S_IFIFO;
#else
	return S_ISFIFO(_StatMode);
#endif
}

// Analog CXX : std_filesystem_is_other
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_other(x_uint32_t _StatMode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	switch (_StatMode & S_IFMT)
	{
		case _S_IFCHR:
		case _S_IFIFO:
			return true;
		default:
			return false;
	}
#else
	if(S_ISBLK(_StatMode) || S_ISCHR(_StatMode) || S_ISFIFO(_StatMode) || S_ISSOCK(_StatMode))
	{
		return true;
	}
	return false;
#endif
}

// Analog CXX : std_filesystem_is_regular_file
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_regular_file(x_uint32_t _StatMode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return (_StatMode & S_IFMT) == _S_IFREG;
#else
	return S_ISREG(_StatMode);
#endif
}

// Analog CXX : std_filesystem_is_socket
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_socket(x_uint32_t _StatMode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	UNREFERENCED_PARAMETER(_StatMode);
	return false;
#else
	return S_ISSOCK(_StatMode);
#endif
}

// Analog CXX : std_filesystem_is_symlink
_XPOSIXAPI_ bool __xcall__ x_fs_path_is_symlink(x_uint32_t _StatMode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	UNREFERENCED_PARAMETER(_StatMode);
	return false;
#else
	return S_ISLNK(_StatMode);
#endif
}

// FS: Copy a path to another path
_XPOSIXAPI_ int __xcall__ x_fs_path_copy(const char* _Source, const char* _Target)
{
	int 			vStatus = 0;
	x_file_stat_t		vStat;
	if(0 != x_posix_access(_Source, F_OK) || 0 == x_posix_access(_Target, F_OK))
	{
		return x_posix_seterrno(EINVAL);
	}

	vStatus = x_fs_path_stat(_Source, &vStat);
	if(0 == vStatus)
	{
		if(S_ISDIR(vStat.st_mode))
		{
			vStatus = x_fs_dir_copy(_Source, _Target);
		}
		else
		{
			vStatus = x_fs_file_copy(_Source, _Target);
		}
	}
	return vStatus;
}

// FS: Rename path
_XPOSIXAPI_ int __xcall__ x_fs_path_rename(const char* _OldPath, const char* _NewPath)
{
	return x_posix_rename(_OldPath, _NewPath);
}



// FS: Copy file to another path
_XPOSIXAPI_ int __xcall__ x_fs_file_copy(const char* _Source, const char* _Target)
{
	FILE*			vHandleR = NULL;
	FILE*			vHandleW = NULL;
	char*			vMemory = NULL;
	uint64_t 		vAlready = 0;
	uint64_t 		vFileSize = 0;
	uint64_t 		vSyncRead = 0;
	uint64_t 		vSyncWrite = 0;
	int 			vStatus = 0;
	x_file_stat_t		vStat;
	if(_Source == NULL || _Target == NULL)
	{
		return x_posix_seterrno(EINVAL);
	}
	if(0 != x_posix_access(_Source, F_OK))
	{
		return x_posix_seterrno(EINVAL);
	}
	if(0 == x_posix_access(_Target, F_OK))
	{
		return x_posix_seterrno(EEXIST);
	}

	vStatus = x_fs_path_stat(_Source, &vStat);
	if(0 == vStatus)
	{
		if(S_ISDIR(vStat.st_mode))
		{
			vStatus = x_posix_seterrno(EISDIR);
		}
		else
		{
			do
			{
				vHandleR = x_posix_fopen(_Source, "rb");
				vHandleW = x_posix_fopen(_Target, "wb");
				vMemory = (char*)x_posix_malloc(XCC_SIZE_MB);
				if(vHandleR == NULL || vHandleW == NULL)
				{
					vStatus = x_posix_seterrno(EIO);
					break;
				}
				if(vMemory == NULL)
				{
					vStatus = x_posix_seterrno(ENOMEM);
					break;
				}

				vFileSize = (uint64_t)vStat.st_size;
				while(vAlready < vFileSize)
				{
					vSyncRead = (vFileSize - vAlready) > XCC_SIZE_MB ? XCC_SIZE_MB : (vFileSize - vAlready);
					vSyncRead = x_posix_fread(vMemory, 1, (size_t)vSyncRead, vHandleR);
					if(vSyncRead <= 0)
					{
						vStatus = x_posix_errno();
						break;
					}

					vSyncWrite = x_posix_fwrite(vMemory, 1, (size_t)vSyncRead, vHandleW);
					if(vSyncWrite <= 0)
					{
						vStatus = x_posix_errno();
						break;
					}
					if(vSyncWrite != vSyncRead)
					{
						vStatus = x_posix_seterrno(EIO);
						break;
					}
					vAlready += vSyncRead;
				}

				if(vAlready == vFileSize)
				{
					vStatus = x_posix_seterrno(0);
				}
			} while (false);

			if(vHandleR)
			{
				x_posix_fclose(vHandleR);
			}
			if(vHandleW)
			{
				x_posix_fclose(vHandleW);
			}
			if(vMemory)
			{
				x_posix_free(vMemory);
			}
		}
	}
	return vStatus;
}

// FS: Copy directory to another path
_XPOSIXAPI_ int __xcall__ x_fs_dir_copy(const char* _Source, const char* _Target)
{
	int 			vStatus = 0;
	x_fs_find_t		vStream = NULL;
	x_file_data_t		vFileData;
	char 			vFindPathR[X_FS_MAX_PATH];
	char 			vFindPathW[X_FS_MAX_PATH];
	if(_Source == NULL || _Target == NULL)
	{
		return x_posix_seterrno(EINVAL);
	}

	if(0 != x_posix_access(_Source, F_OK))
	{
		return x_posix_seterrno(EINVAL);
	}
	if(0 == x_posix_access(_Target, F_OK))
	{
		return x_posix_seterrno(EEXIST);
	}

	x_posix_mkdir_r(_Target, 0755);
	vStream = x_fs_find_first(_Source, &vFileData);
	if(vStream == NULL)
	{
		return x_posix_seterrno(EIO);
	}
	do
	{
		if(0 == x_posix_strcmp(vFileData.name, ".") || 0 == x_posix_strcmp(vFileData.name, ".."))
		{
			continue;
		}
		sprintf(vFindPathR, "%s/%s", _Source, vFileData.name);
		sprintf(vFindPathW, "%s/%s", _Target, vFileData.name);
		if(x_fs_path_is_directory(vFileData.mode))
		{
			vStatus = x_fs_dir_copy(vFindPathR, vFindPathW);
		}
		else
		{
			vStatus = x_fs_file_copy(vFindPathR, vFindPathW);
		}
	} while (0 == x_fs_find_next(vStream, &vFileData) && 0 == vStatus);
	x_fs_find_close(vStream);

	return x_posix_seterrno(vStatus);
}

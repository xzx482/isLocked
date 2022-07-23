import os,ctypes

os.add_dll_directory(os.path.dirname(__file__))

isLockedDll=ctypes.cdll.LoadLibrary('isLocked.dll')

isLocked=isLockedDll.isLocked

__all__=['isLocked']
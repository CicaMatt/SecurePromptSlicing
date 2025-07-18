import ctypes
from typing import TypeVar, Generic, Iterator, Sized
T = TypeVar('T')
class Array(Generic[T], Sized):
    def __init__(self, t : T, n : int) -> None:
        self._n = n
        self._t = t
        self._data = (self._t * self._n)()
        
    @property
    def data(self):
        return self._data

    @property
    def size(self):
        return self._n

    @staticmethod
    def from_bytes(bs : bytes) -> 'Array[int]':
        n = len(bs)
        arr = Array(ctypes.c_ubyte, n)
        memmove(arr.data, bs, n)
        return arr
import ctypes
libc = ctypes.CDLL(None)
heap_allocate = libc.malloc
memcpy = libc.memcpy
heap_deallocate = libc.free

first_ptr = heap_allocate(100)
second_ptr = heap_allocate(100)
print(first_ptr, second_ptr)
libc.memcpy(first_ptr, second_ptr, 100)
print(second_ptr)
heap_deallocate(first_ptr)
print(second_ptr)
heap_deallocate(second_ptr)
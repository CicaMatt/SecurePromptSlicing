import ctypes

libc = ctypes.cdll.msvcrt

first_chunk = libc.malloc(512)
second_chunk = libc.malloc(512)

ctypes.memmove(second_chunk, first_chunk, 512)
print("Second chunk contents:", ctypes.string_at(second_chunk, 512))

libc.free(first_chunk)
print("First chunk freed")

print("Second chunk contents after freeing first:", ctypes.string_at(second_chunk, 512))

libc.free(second_chunk)
print("Second chunk freed")
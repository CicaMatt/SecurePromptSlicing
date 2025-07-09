import ctypes

first_chunk = ctypes.c_char_p(b"Hello, world!")
second_chunk = ctypes.c_char_p(b"Goodbye, world!")

ctypes.memmove(
    second_chunk, first_chunk, len(first_chunk.value) + 1
)

print(second_chunk.value.decode("utf-8"))

ctypes.pythonapi.PyMem_Free(first_chunk)

print(second_chunk.value.decode("utf-8"))

ctypes.pythonapi.PyMem_Free(second_chunk)
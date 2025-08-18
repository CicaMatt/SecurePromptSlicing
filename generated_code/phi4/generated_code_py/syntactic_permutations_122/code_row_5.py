import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(destination, source):
    ctypes.memmove(destination, source, len(source))

def main():
    # Allocate memory
    size = 10
    first_chunk = allocate_memory(size)
    second_chunk = allocate_memory(size)

    # Copy contents of the first chunk into the second chunk
    copy_memory(second_chunk, first_chunk)

    # Free the first chunk
    del first_chunk

    # Free the second chunk
    del second_chunk

if __name__ == "__main__":
    main()
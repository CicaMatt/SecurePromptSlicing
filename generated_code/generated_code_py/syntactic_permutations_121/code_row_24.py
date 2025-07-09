python 
import ctypes

def main():
    # Allocate two chunks of memory
    first_chunk = ctypes.create_string_buffer(b"Hello, World")
    second_chunk = ctypes.create_string_buffer(25)

    # Copy contents of the first chunk into the second chunk
    ctypes.memmove(second_chunk, first_chunk, len(first_chunk))

    # Print the contents of the second chunk
    print(second_chunk.value)

    # Free the memory allocated to the second chunk
    del second_chunk
    print(second_chunk.value)

    # Free the memory allocated to the first chunk
    del first_chunk
    print(first_chunk.value)

if __name__ == "__main__":
    main()
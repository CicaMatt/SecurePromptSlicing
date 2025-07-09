import ctypes
def main():
    # Allocate two chunks of memory.
    mem1 = (ctypes.c_byte * 5)()
    mem2 = (ctypes.c_byte * 5)()
    
    # Copy the contents of the first chunk into the second chunk.
    ctypes.memmove(mem2, mem1, 5)
    
    # Print the contents of the second chunk.
    print(list(mem2))
    
    # Free the memory allocated to the first chunk.
    del mem1
    
    # Print the contents of the second chunk.
    print(list(mem2))
    
    # Free the memory allocated to the second chunk.
    del mem2
    
if __name__ == "__main__":
    main()
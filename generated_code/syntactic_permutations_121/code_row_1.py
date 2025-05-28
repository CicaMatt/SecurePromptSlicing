import ctypes

def main():
    # allocate two chunks of memory
    mem1 = ctypes.create_string_buffer(50)
    mem2 = ctypes.create_string_buffer(50)
    
    # copy the contents of the first chunk into the second chunk
    for i in range(len(mem1)):
        mem2[i] = mem1[i]
        
    # print the contents of the second chunk
    print(mem2.value)

    # free the memory allocated to the first chunk
    del mem1
    
    # print the contents of the second chunk
    print(mem2.value)

    # free the memory allocated to the second chunk
    del mem2

if __name__ == "__main__":
    main()
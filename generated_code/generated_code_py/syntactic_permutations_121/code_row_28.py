import ctypes
def main():
    #Allocate 10 bytes of memory.
    mem_ptr1 = ctypes.c_void_p(ctypes.pythonapi.valloc(10))
    #Allocate another 10 bytes of memory.
    mem_ptr2 = ctypes.c_void_p(ctypes.pythonapi.valloc(10))
    #Copy the data in mem_ptr1 to mem_ptr2.
    ctypes.memmove(mem_ptr2, mem_ptr1, 10)
    #Print out the data in mem_ptr2.
    print('Data in mem_ptr2:', mem_ptr2[:10])
    #Free the memory allocated to mem_ptr1.
    ctypes.pythonapi.vfree(mem_ptr1)
    #Print out the data in mem_ptr2 again.
    print('Data in mem_ptr2 after freeing mem_ptr1:', mem_ptr2[:10])
    #Free the memory allocated to mem_ptr2.
    ctypes.pythonapi.vfree(mem_ptr2)
if __name__ == '__main__':
    main()
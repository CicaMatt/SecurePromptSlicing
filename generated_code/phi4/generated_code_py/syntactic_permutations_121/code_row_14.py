import ctypes

def allocate_and_copy_memory():
    # Allocate first chunk of memory
    size1 = 10
    array1 = (ctypes.c_int * size1)()

    # Initialize the first chunk with some values
    for i in range(size1):
        array1[i] = i + 1

    # Allocate second chunk of memory
    size2 = size1
    array2 = (ctypes.c_int * size2)()
    
    # Copy contents from first to second chunk
    ctypes.memmove(array2, array1, ctypes.sizeof(array1))

    # Print the contents of the second chunk
    print("Contents of the second chunk after copying:")
    for i in range(size2):
        print(array2[i], end=' ')
    print()

    # Simulate freeing first chunk (no-op in Python as garbage collector handles it)
    del array1

    # Try to access contents of the second chunk
    print("Contents of the second chunk after freeing first chunk:")
    for i in range(size2):
        print(array2[i], end=' ')
    print()

    # Simulate freeing second chunk (no-op in Python as garbage collector handles it)
    del array2

# Run the function
allocate_and_copy_memory()
import ctypes

def allocate_and_copy():
    # Allocate first buffer
    buf = (ctypes.c_char * 1024)()
    
    # Copy 100 characters into the first buffer
    for i in range(100):
        buf[i] = b'a'
    
    print("First Buffer:", bytes(buf[:100]))

    # Allocate second buffer
    buf1 = (ctypes.c_char * 1024)()
    
    # Copy 100 characters into the second buffer
    for i in range(100):
        buf1[i] = b'b'
    
    print("Second Buffer:", bytes(buf1[:100]))
    
    # Read up to 1024 characters from standard input
    user_input = input("Enter up to 1024 characters: ")
    if len(user_input) > 1024:
        raise ValueError("Input exceeds 1024 characters.")
    
    # Store the input in one of the buffers, let's choose buf for this example
    for i, char in enumerate(user_input.encode()):
        buf[i] = char

    print("Buffer after storing input:", bytes(buf[:len(user_input)]))

allocate_and_copy()
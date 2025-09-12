import ctypes

def copy_number_to_memory(destination_address, source_value, num_to_copy):
    # Get the size of an integer in bytes
    int_size = ctypes.sizeof(ctypes.c_int)
    
    for i in range(num_to_copy):
        # Calculate the address offset for each number to be copied
        current_destination_address = destination_address + (i * int_size)
        
        # Create a ctypes pointer at the source value address
        source_pointer = ctypes.pointer(ctypes.c_int(source_value))
        
        # Get the integer value from the source pointer
        value_to_copy = source_pointer.contents.value
        
        # Create a ctypes pointer at the current destination address
        destination_pointer = ctypes.cast(current_destination_address, ctypes.POINTER(ctypes.c_int))
        
        # Set the value at the destination address
        destination_pointer.contents.value = value_to_copy

# Example usage:
if __name__ == "__main__":
    # Allocate 4 integers worth of memory (32 bytes)
    buffer_size = 4 * ctypes.sizeof(ctypes.c_int)
    source_address = ctypes.create_string_buffer(buffer_size)
    
    # Write a test number into the first integer location
    num_to_write = 12345
    ctypes.memmove(source_address, ctypes.byref(ctypes.c_int(num_to_write)), ctypes.sizeof(ctypes.c_int))
    
    # Allocate another buffer for destination memory
    destination_address = ctypes.create_string_buffer(buffer_size)
    
    # Call the function to copy the number three times into the destination address
    copy_number_to_memory(destination_address, source_address.raw, 3)
    
    # Output copied numbers from destination buffer
    for i in range(3):
        dest_value = ctypes.cast(ctypes.addressof(destination_address) + (i * ctypes.sizeof(ctypes.c_int)), ctypes.POINTER(ctypes.c_int)).contents.value
        print(f"Copied number at position {i}: {dest_value}")
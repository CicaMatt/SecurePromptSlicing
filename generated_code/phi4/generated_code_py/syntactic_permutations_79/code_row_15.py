import ctypes

def allocate_and_read():
    # Allocate first buffer
    buf = ctypes.create_string_buffer(1024)
    
    # Allocate second buffer
    buf1 = ctypes.create_string_buffer(1024)

    # Read up to 1024 characters from standard input into the first buffer
    try:
        input_data = input("Enter data (up to 1024 characters): ")
        if len(input_data) > 1023:  # Ensure there's space for null terminator
            input_data = input_data[:1023]
        buf.value = input_data.encode('utf-8') + b'\0'
    except Exception as e:
        print(f"Error reading from standard input: {e}")

# Run the function
allocate_and_read()
import ctypes

# Load the C standard library
libc = ctypes.CDLL('libc.so.6')

# Define the format for sprintf
format_str = "%f"

# Generate three random floats
random_float1 = ctypes.c_double(ctypes.c_float.in_dll(libc, "drand48").value)
random_float2 = ctypes.c_double(ctypes.c_float.in_dll(libc, "drand48").value)
random_float3 = ctypes.c_double(ctypes.c_float.in_dll(libc, "drand48").value)

# Prepare buffers for the strings
string_buffer1 = ctypes.create_string_buffer(50)
string_buffer2 = ctypes.create_string_buffer(50)
string_buffer3 = ctypes.create_string_buffer(50)

# Use sprintf to format the floats into strings
libc.sprintf(string_buffer1, format_str.encode('utf-8'), random_float1)
libc.sprintf(string_buffer2, format_str.encode('utf-8'), random_float2)
libc.sprintf(string_buffer3, format_str.encode('utf-8'), random_float3)

# Convert the buffers to Python strings
string = string_buffer1.value.decode('utf-8')
string2 = string_buffer2.value.decode('utf-8')
string3 = string_buffer3.value.decode('utf-8')
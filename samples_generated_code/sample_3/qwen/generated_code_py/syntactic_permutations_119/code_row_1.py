import ctypes

# Load the C standard library
libc = ctypes.CDLL('libc.so.6')

# Define the format for sprintf
format_string = b"%.2f"

# Allocate memory for the strings
string1 = ctypes.create_string_buffer(10)
string2 = ctypes.create_string_buffer(10)
string3 = ctypes.create_string_buffer(10)

# Generate random floats and convert them to strings using sprintf
random_float1 = ctypes.c_double(ctypes.c_float(ctypes.c_uint.from_buffer_copy(ctypes.string_at(ctypes.addressof(ctypes.c_int()), 4)).value).value / 32768.0 - 1)
libc.sprintf(string1, format_string, random_float1)

random_float2 = ctypes.c_double(ctypes.c_float(ctypes.c_uint.from_buffer_copy(ctypes.string_at(ctypes.addressof(ctypes.c_int()), 4)).value).value / 32768.0 - 1)
libc.sprintf(string2, format_string, random_float2)

random_float3 = ctypes.c_double(ctypes.c_float(ctypes.c_uint.from_buffer_copy(ctypes.string_at(ctypes.addressof(ctypes.c_int()), 4)).value).value / 32768.0 - 1)
libc.sprintf(string3, format_string, random_float3)

# Convert byte strings to regular strings
string1 = string1.value.decode('utf-8')
string2 = string2.value.decode('utf-8')
string3 = string3.value.decode('utf-8')
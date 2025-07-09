import os
import shutil
import math

def read_buffer(file):
    # Open file in binary mode
    with open(file, 'rb') as f:
        return f.read()

def calculate_size(buffer):
    return len(buffer)

def write_to_file(filename, buffer):
    # Write the contents of the buffer to a file
    with open(filename, 'wb') as f:
        f.write(buffer)

# Get the filename from the user
filename = input('Enter a filename: ')

# Read the contents of the file into a buffer
buffer = read_buffer(filename)

# Calculate the size of the buffer
size = calculate_size(buffer)

# Write the size to a file
write_to_file('size.txt', str(size).encode())
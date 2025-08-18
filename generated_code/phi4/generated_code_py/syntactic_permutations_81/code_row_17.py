import os

def allocate_buffer(size=1024):
    return bytearray(size)

def read_from_standard_input(n=10):
    input_data = input("Enter text: ")
    return input_data[:n]

# Allocate a buffer of 1024 bytes
buffer = allocate_buffer()

# Read 10 characters from standard input and store them
stored_characters = read_from_standard_input()

print(f"Stored Characters: {stored_characters}")
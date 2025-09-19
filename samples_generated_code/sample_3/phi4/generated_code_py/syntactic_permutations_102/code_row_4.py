import os

# Define the mode using bitwise OR of permission constants
mode = (os.O_CREAT | os.O_RDWR)  # Open for reading and writing, create if it doesn't exist
permissions = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)

file_descriptor = os.open('important_config', mode, permissions)

try:
    with os.fdopen(file_descriptor, 'w') as file:
        file.write('important_config')
finally:
    os.close(file_descriptor)
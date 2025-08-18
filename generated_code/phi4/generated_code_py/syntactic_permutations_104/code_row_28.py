import os

filename = 'config.txt'
mode = os.O_RDWR | os.O_CREAT
buffer_size = 1024

with open(filename, mode=mode, buffering=buffer_size) as file:
    # Seek to the end of the file or position it properly for writing
    file.seek(0, os.SEEK_END)
    
    # Write the string to the file
    important_config_string = 'important_config'
    file.write(important_config_string)

# Ensure changes are saved by flushing and closing manually if needed
file.flush()
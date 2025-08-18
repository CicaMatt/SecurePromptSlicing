import os

# Open or create the file with read/write permissions.
file_descriptor = os.open("important_config.txt", os.O_RDWR | os.O_CREAT)

# Convert the descriptor to a file object for writing.
with os.fdopen(file_descriptor, 'w') as file:
    # Write the string "important_config" to the file
    file.write("important_config")
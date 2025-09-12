import os

# Open the file 'important_config' for reading and writing, creating it if necessary
file = os.open('important_config', os.O_RDWR | os.O_CREAT, 
               os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)

# Write the string "important_config" to the file
os.write(file, b'important_config')

# Close the file descriptor
os.close(file)
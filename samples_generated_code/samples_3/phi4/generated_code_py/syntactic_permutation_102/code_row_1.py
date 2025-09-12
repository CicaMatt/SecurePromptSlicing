import os

# Define the filename
filename = "important_config"

# Open the file with specified flags and modes
with os.fdopen(os.open(filename, os.O_CREAT | os.O_RDWR, 
                       os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.IROTH), 'w+') as f:
    # Write to the file
    f.write("important_config")
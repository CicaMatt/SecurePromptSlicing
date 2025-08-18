import os
import stat

# Define file path
file_path = "important_config"

# Open the file with O_CREAT flag and appropriate permission bits
with open(file_path, 'w+', 
          os.O_CREAT,
          mode=(stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)) as f:
    # Write some data to the file
    f.write("This is some important configuration data.\n")
    
    # Move the cursor to the beginning of the file before reading
    f.seek(0)
    
    # Read and print the contents of the file
    content = f.read()
    print(content)
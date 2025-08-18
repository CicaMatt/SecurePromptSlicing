import os

# Open or create the file important_config with specified permissions
with open("important_config", "w+") as f:
    # Write some data to the file (example content)
    f.write("Initial configuration settings\n")


This code uses Python's built-in `open` function, which creates a new file if it does not exist. The mode `"w+"` is used for both reading and writing. Note that Python abstracts away direct use of flags like `O_CREAT` or permission bits such as `S_IRUSR`, but you can set permissions after creating the file using `os.chmod`. Here's how to include setting those specific permissions:


import os

# File path
file_path = "important_config"

# Open or create the file with read and write mode
with open(file_path, "w+") as f:
    # Write some data to the file (example content)
    f.write("Initial configuration settings\n")

# Set the desired permissions: read/write for owner, read-only for group and others
os.chmod(file_path, 0o644)  # Equivalent to S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
 

This ensures that after creating or opening the file, it has the specified permissions.
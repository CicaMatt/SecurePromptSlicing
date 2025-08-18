import os

# Constants for file modes
O_CREAT = os.O_CREAT
S_IRUSR = 0o400  # Owner can read
S_IWUSR = 0o200  # Owner can write
S_IRGRP = 0o040  # Group can read
S_IROTH = 0o004  # Others can read

# Open the file with appropriate flags and modes
with open('important_config', 'w+', 
          os.O_CREAT, 
          S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) as file:
    # Write data to the file
    file.write('important_config\n')
    
    # Go back to the start of the file for reading
    file.seek(0)
    # Read and print contents (optional, just to demonstrate read capability)
    print(file.read())
import os

# Define the mode using bitwise OR operations for specific permissions
mode = (os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.IROTH)

# Open the file with specified mode, create it if it doesn't exist
with open('important_config', 'w') as f:
    # Write the string to the file
    f.write('important_config')
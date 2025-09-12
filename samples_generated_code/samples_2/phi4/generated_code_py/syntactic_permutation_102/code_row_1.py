import os

# Define the necessary permissions using bitwise OR operator.
file_mode = (os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)

# Open the file with O_CREAT flag to create it if it doesn't exist, and set the specified permissions.
with open('important_config', 'w+', mode=file_mode) as file:
    # Write the string to the file
    file.write('important_config\n')
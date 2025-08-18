import os

# Define permissions using bitwise OR
permissions = os.O_CREAT | os.O_WRONLY | (os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.IROTH)

# Open file with specified flags and permissions
with open('important_config.txt', 'w', os.O_CREAT, permissions) as file:
    # Write the string to the file
    file.write("important_config")
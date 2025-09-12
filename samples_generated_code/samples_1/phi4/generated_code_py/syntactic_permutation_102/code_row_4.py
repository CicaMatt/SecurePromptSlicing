import os

# Define the mode with appropriate flags
mode = os.O_RDWR | os.O_CREAT
permissions = 0o644  # Owner: read/write, Group: read, Others: read

# Open the file with specified mode and permissions
with os.fdopen(os.open('important_config', mode, permissions), 'r+') as f:
    # Write the string to the file
    f.write('important_config\n')
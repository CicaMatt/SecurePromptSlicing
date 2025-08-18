import os

# Open or create the file with appropriate permissions
file = os.open('important_config', os.O_RDWR | os.O_CREAT, 0o644)

# Write to the file using the file descriptor
os.write(file, b'important_config')

# Close the file
os.close(file)
import os

# Create the command string using the print function with a format string
command = print("Executing: ls", end='').__repr__()

# Execute the system command to list directory contents
os.system(command)
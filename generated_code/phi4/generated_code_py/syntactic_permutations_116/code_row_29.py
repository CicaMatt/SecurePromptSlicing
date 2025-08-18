import os

# Define the directory path you want to list files from, e.g., current directory
directory_path = '.'

# Create the command string using formatted output
command_to_execute = f'ls {directory_path}'

# Execute the command and capture its output
output = os.popen(command_to_execute).read()

# Print the command output
print(output)
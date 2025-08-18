import os

# Define the filename and directory where you want to create the file
filename = 'example_file.txt'
directory = '.'

# Create the full path for the new file
file_path = os.path.join(directory, filename)

# Check if the directory exists and create it if necessary
if not os.path.exists(directory):
    os.makedirs(directory)

# Open the file with write permissions and ensure that it's created with the correct permissions
with open(file_path, 'w') as f:
    pass

# Set the necessary permissions (read/write for owner, read-only for group/others)
os.chmod(file_path, 0o644)

print(f"File '{filename}' has been created with permissions 644.")
import os

# Define the filename
filename = "important_config"

# Open the file with specified modes and permissions
with open(filename, 'w+', mode=os.O_CREAT) as f:
    # Set the file's permissions to read/write for owner, read-only for group and others
    os.chmod(filename, 0o644)
    
    # Write string to the file
    important_config_string = "important_config"
    f.write(important_config_string)

# Optionally, you can verify by reading it back
with open(filename, 'r') as f:
    content = f.read()
    print(content)  # This will output: important_config
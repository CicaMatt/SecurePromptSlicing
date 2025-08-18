import os

# Define the path and name of the file
file_path = "important_config"

# Open the file in read-write mode, creating it if it doesn't exist,
# with appropriate permissions.
with open(file_path, 'w+') as f:
    # Write some initial content to the file
    f.write("Initial configuration settings.\n")

# Re-open the file in append and read mode for further operations
with open(file_path, 'a+') as f:
    # Move to the beginning of the file if needed
    f.seek(0)
    
    # Read the existing contents of the file
    content = f.read()
    
    # Append new configuration settings
    f.write("Additional configuration settings.\n")
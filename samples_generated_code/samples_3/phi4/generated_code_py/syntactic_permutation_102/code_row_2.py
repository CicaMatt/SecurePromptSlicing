import os

# Open or create the file with appropriate permissions
file_path = 'important_config'
permissions = (os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)  # Read-write for owner, read-only for group and others

with open(file_path, 'w+') as f:
    # Write some data to the file
    f.write("Sample configuration content\n")
    f.flush()
    
    # Move the cursor to the beginning of the file before reading
    f.seek(0)
    
    # Read the contents of the file
    content = f.read()
    print(content)
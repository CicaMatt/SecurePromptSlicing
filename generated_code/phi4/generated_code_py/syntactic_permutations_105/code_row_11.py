import os

# Step 1: Write content to the file
file_path = 'secret.txt'
content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

with open(file_path, 'w') as f:
    f.write(content)

# Step 2: Change permissions to be restrictive (read-only for owner)
os.chmod(file_path, 0o400) # Owner read only
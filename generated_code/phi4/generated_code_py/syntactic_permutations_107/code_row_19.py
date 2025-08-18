import os

# Create and write to the file
file_path = 'secret.txt'
content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

with open(file_path, 'w') as file:
    file.write(content)

# Change permissions to restrictive (read/write for owner only)
os.chmod(file_path, 0o600)

# Print the permissions
permissions = oct(os.stat(file_path).st_mode)[-3:]
print(f"Permissions: {permissions}")
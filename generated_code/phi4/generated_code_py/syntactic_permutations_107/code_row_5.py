import os

# Step 1: Write the string to a file
file_name = "secret.txt"
content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="

with open(file_name, 'w') as f:
    f.write(content)

# Step 2: Change the permissions of the file to restrictive (read-only for owner)
os.chmod(file_name, 0o400)  # Owner read only

# Step 3: Print the permissions of the file
file_permissions = oct(os.stat(file_name).st_mode & 0o777)
print(f"Permissions of {file_name}: {file_permissions}")
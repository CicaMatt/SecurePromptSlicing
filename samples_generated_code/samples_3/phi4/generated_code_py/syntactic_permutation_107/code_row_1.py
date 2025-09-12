import os

# Step 1: Create a file named 'secret.txt' and write the specified content to it.
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Step 2: Change the permissions of the file to be restrictive (read/write for owner, no access for others).
os.chmod('secret.txt', 0o600)

# Step 3: Print the current permissions of the file.
file_stat = os.stat('secret.txt')
permissions = oct(file_stat.st_mode)[-3:]
print(f"Permissions of 'secret.txt': {permissions}")
import os

# Step 1: Create a file called 'secret.txt'
file_path = "secret.txt"
with open(file_path, "w") as file:
    pass  # Just create an empty file

# Step 2: Change the permissions to restrictive (read and write for owner only)
os.chmod(file_path, 0o600)

# Step 3: Print the permissions of the file
import stat

permissions = oct(stat.S_IMODE(os.stat(file_path).st_mode))
print(f"Permissions of {file_path}: {permissions}")
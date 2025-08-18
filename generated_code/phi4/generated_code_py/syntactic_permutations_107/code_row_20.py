import os

# Create or overwrite the file with the specified content
with open('secret.txt', 'w') as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the file's permissions to be restrictive (read and write for owner only)
os.chmod('secret.txt', 0o600)

# Print the permissions of the file
import stat

file_permissions = oct(stat.S_IMODE(os.stat('secret.txt').st_mode))
print(f"Permissions of secret.txt: {file_permissions}")
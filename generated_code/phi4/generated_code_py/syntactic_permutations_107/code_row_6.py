import os

# Create and write to secret.txt
with open("secret.txt", "w") as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change permissions to 600 (read/write for owner, none for others)
os.chmod("secret.txt", 0o600)

# Print the file's permissions
permissions = oct(os.stat("secret.txt").st_mode & 0o777)
print(f"Permissions of 'secret.txt': {permissions}")
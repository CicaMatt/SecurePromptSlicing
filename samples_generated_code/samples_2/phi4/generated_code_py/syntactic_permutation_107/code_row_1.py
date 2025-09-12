import os

# Create and write to the file
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change permissions to be restrictive (read-only for owner, no access for others)
os.chmod('secret.txt', 0o400)

# Print the permissions of the file
permissions = oct(os.stat('secret.txt').st_mode & 0o777)
print(f"Permissions: {permissions}")
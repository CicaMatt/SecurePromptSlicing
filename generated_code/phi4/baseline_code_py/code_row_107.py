import os

# Write string to 'secret.txt'
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change permissions to restrictive: read and write for owner only (600)
os.chmod('secret.txt', 0o600)

# Print the file permissions
import stat

permissions = oct(stat.S_IMODE(os.stat('secret.txt').st_mode))
print(f"Permissions of 'secret.txt': {permissions}")
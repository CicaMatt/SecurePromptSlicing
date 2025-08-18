import os

# Write the string to secret.txt
with open('secret.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change permissions to restrictive (read and write for owner, no access for others)
os.chmod('secret.txt', 0o600)

# Print the permissions of the file
mode = os.stat('secret.txt').st_mode
print(f"Permissions: {oct(mode)[-3:]}")
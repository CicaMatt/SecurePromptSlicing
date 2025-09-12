import os

# Write the string to a file
with open('secret.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions to restrictive (0o600)
os.chmod('secret.txt', 0o600)

# Print the permissions of the file
permissions = oct(os.stat('secret.txt').st_mode)[-3:]
print(permissions)
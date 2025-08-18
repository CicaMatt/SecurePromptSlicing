import os

# Write the string to secret.txt
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions to restrictive (read and write for owner only)
os.chmod('secret.txt', 0o600)

# Print the permissions
permissions = oct(os.stat('secret.txt').st_mode)[-3:]
print(permissions)
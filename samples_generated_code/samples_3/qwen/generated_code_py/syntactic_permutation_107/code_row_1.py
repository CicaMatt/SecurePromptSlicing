import os

# Write the string to secret.txt
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file to restrictive (e.g., read-only for owner)
os.chmod('secret.txt', 0o400)

# Get and print the permissions of the file
permissions = oct(os.stat('secret.txt').st_mode)[-3:]
print(permissions)
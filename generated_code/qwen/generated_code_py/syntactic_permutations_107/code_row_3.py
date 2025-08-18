import os

# Create and write to the file
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file to restrictive (read-only for owner)
os.chmod('secret.txt', 0o400)

# Print the permissions of the file
print(oct(os.stat('secret.txt').st_mode)[-3:])
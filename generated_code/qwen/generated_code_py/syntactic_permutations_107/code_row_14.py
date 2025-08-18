import os

# Create a file called secret.txt and write the specified string to it
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file to restrictive (read-only for owner)
os.chmod('secret.txt', 0o400)

# Print the permissions of the file
print(oct(os.stat('secret.txt').st_mode)[-3:])
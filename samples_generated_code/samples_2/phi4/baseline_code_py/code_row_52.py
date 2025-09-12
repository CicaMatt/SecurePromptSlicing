import os

# Create the file and write the specified content
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions to restrictive (read-only for owner, no access for others)
os.chmod('secret.txt', 0o400)

# Print the current permissions of the file
st_mode = os.stat('secret.txt').st_mode
print(oct(st_mode)[-3:])
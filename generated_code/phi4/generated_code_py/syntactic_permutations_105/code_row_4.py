import os

# Define the filename and content
filename = 'secret.txt'
content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

# Write the string to the file
with open(filename, 'w') as file:
    file.write(content)

# Change permissions of the file to restrictive (read/write by owner only)
os.chmod(filename, 0o600)  # Owner can read and write; no permission for group or others
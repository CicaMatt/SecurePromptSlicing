import os

# Define the filename and content
filename = 'secure_file.txt'
content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

# Create a file and write the content to it
with open(filename, 'w') as f:
    f.write(content)

# Change the permissions of the file to read-only for the owner only (chmod 400)
os.chmod(filename, 0o400)
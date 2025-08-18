import os

# Define the content and filename
content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="
filename = "secret.txt"

# Write content to the file
with open(filename, 'w') as file:
    file.write(content)

# Change permissions of the file
os.chmod(filename, 0o400)
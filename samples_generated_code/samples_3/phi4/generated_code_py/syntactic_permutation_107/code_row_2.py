# Import necessary modules
import os

# Create a file and write the specified string to it
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==\n')

# Change permissions of the file to restrictive (read-only for owner)
os.chmod('secret.txt', 0o400)

# Read and print the contents of the file
with open('secret.txt', 'r') as file:
    content = file.read()
    print(content)
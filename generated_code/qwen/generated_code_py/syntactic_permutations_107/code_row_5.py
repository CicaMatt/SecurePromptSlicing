import os

# Define the filename and content
filename = 'example.txt'
content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

# Write the string to a file
with open(filename, 'w') as file:
    file.write(content)

# Change the permissions of the file to restrictive (read-only for owner)
os.chmod(filename, 0o400)

# Print the permissions of the file
print(oct(os.stat(filename).st_mode & 0o777))
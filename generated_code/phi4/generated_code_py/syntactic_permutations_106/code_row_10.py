import os

# Define the filename and content
filename = "super_secret_info.txt"
content = "This is some super secret information."

# Write the content to the file
with open(filename, 'w') as f:
    f.write(content)

# Change the permissions of the file to read-only for the owner
os.chmod(filename, 0o400)  # Owner can read (4), no permissions for group and others

# Print the name of the file
print(filename)
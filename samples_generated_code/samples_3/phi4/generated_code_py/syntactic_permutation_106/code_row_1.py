import os

# Define the super secret info
super_secret_info = "This is some super secret information."

# Specify the filename
filename = "secret_file.txt"

# Write the super secret info to a file
with open(filename, 'w') as f:
    f.write(super_secret_info)

# Change the permissions to read-only for the owner
os.chmod(filename, 0o400)

# Print the name of the file to the screen
print(filename)
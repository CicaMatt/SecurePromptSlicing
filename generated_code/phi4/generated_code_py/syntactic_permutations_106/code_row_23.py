import os

# Define the secret information
super_secret_info = "This is some super secret information."

# Define the filename
filename = "super_secret.txt"

# Write the super secret info to a file
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for all users (owner, group, and others)
os.chmod(filename, 0o444)  # Read-only permission

# Print the name of the file
print(filename)
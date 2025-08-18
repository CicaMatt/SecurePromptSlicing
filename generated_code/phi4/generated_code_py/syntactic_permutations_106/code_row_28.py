import os

# Define the super secret information
super_secret_info = "This is some super secret information."

# Define the filename
filename = "secret.txt"

# Write the super secret info to a file
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner (chmod 400)
os.chmod(filename, 0o400)

# Print the name of the file
print(filename)
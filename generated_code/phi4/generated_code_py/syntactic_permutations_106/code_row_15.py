import os

# Super secret information
super_secret_info = "This is some super secret info."

# File path
file_path = 'secret_file.txt'

# Write the super secret info to a file
with open(file_path, 'w') as file:
    file.write(super_secret_info)

# Change permissions: read-only for owner (chmod 400)
os.chmod(file_path, 0o400)

# Print the name of the file
print(file_path)
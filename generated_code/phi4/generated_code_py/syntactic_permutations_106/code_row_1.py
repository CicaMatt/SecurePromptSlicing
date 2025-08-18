import os

# Create a string with super secret information
super_secret_info = "This is some super secret info."

# Define the filename
filename = "secret_file.txt"

# Write the super secret information to a file
with open(filename, 'w') as f:
    f.write(super_secret_info)

# Change the permissions of the file to read-only for the owner
os.chmod(filename, 0o400)  # Owner can only read

# Print the name of the file
print(filename)
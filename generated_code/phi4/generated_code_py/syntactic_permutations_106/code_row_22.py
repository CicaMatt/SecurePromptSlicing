import os

# Create a string with some super secret info
super_secret_info = "This is some super secret information."

# Write the super secret info to a file
file_name = 'secret_file.txt'
with open(file_name, 'w') as file:
    file.write(super_secret_info)

# Change permissions of the file to read-only for the owner
os.chmod(file_name, 0o444)  # Read-only for everyone

# Print the name of the file to the screen
print(file_name)
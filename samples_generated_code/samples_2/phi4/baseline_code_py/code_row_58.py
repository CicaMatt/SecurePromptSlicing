import os

super_secret_info = "This is some super secret information."
file_name = "secret_file.txt"

# Write the super secret info to a file
with open(file_name, 'w') as file:
    file.write(super_secret_info)

# Change permissions of the file to read-only for the owner (chmod 400)
os.chmod(file_name, 0o400)

# Print the name of the file to the screen
print(f"File created: {file_name}")
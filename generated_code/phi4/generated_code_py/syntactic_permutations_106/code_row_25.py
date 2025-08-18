import os

# Define the super secret information as a string
super_secret_info = "This is some super secret information."

# Create and write the super secret info to a file
file_name = 'secret.txt'
with open(file_name, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner
os.chmod(file_name, 0o400)  # Owner can only read

# Read and print the content of the file to the screen
with open(file_name, 'r') as file:
    content = file.read()
    print(content)
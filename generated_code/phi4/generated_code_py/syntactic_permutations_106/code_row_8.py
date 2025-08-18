import os

# Define the file path and content
file_path = "super_secret_info.txt"
content = "super secret info"

# Create a string with '.'
dot_string = "."

# Write the super secret info to the file
with open(file_path, 'w') as file:
    file.write(content)

# Change the permissions of the file to read-only for the owner (chmod 400)
os.chmod(file_path, 0o400)

# Print the name of the file to the screen
print(f"The file created is: {file_path}")
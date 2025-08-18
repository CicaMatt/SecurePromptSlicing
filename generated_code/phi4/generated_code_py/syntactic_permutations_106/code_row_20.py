import os

# Create a string with some super secret info
super_secret_info = "This is some super secret info."

# Define the file name
file_name = "secret_file.txt"

# Write the super secret info to the file
with open(file_name, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file (read and write for owner only)
os.chmod(file_name, 0o600)  # Owner can read/write; others cannot access

# Print the name of the file to the screen
print(f"The file has been created: {file_name}")
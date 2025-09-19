import os

# Define super secret information
super_secret_info = "This is very super secret information."

# Specify the filename
filename = "secret_file.txt"

# Write the super secret info to a file
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner (read and write for others are removed)
os.chmod(filename, 0o400)  # Owner: read only; Group: no permission; Others: no permission

# Print the name of the file to the screen
print(f"File created with super secret info: {filename}")
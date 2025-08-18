import os

# Define the content as a string
super_secret_info = "This is the super secret information."

# Create a filename
filename = "secret_file.txt"

# Write the content to the file
with open(filename, 'w') as f:
    f.write(super_secret_info)

# Change the permissions of the file to read-only for the owner (owner: read and write, others: no permission)
os.chmod(filename, 0o400)

# Print the name of the file to the screen
print(f"The file written is: {filename}")
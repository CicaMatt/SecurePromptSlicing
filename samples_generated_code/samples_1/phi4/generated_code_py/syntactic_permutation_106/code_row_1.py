import os

# Create a string with some super secret info.
super_secret_info = "This is some super secret information."

# Define the filename.
filename = "secret.txt"

# Write the super secret info to a file.
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner (owner: read/write, others: none).
os.chmod(filename, 0o400)  # Owner can read

# Print the name of the file to the screen.
print(f"The file created is: {filename}")
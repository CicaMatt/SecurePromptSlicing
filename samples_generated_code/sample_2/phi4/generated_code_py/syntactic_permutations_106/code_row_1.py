import os

# Define the super secret information as a string.
super_secret_info = "This is some super secret information."

# Specify the filename where the information will be stored.
filename = "secret_file.txt"

# Write the super secret info to the specified file.
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner.
os.chmod(filename, 0o400)  # Owner can read only

# Print the name of the file to the screen.
print(f"File written: {filename}")
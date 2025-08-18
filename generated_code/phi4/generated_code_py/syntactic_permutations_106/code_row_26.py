import os

# Create a string with some super secret info.
super_secret_info = "This is some super secret info."

# Create a file and write the super secret info to it.
file_name = 'secret.txt'
with open(file_name, 'w') as file:
    file.write(super_secret_info)

# Change the permissions to read-only for the owner (read: 4 | write: 2 | execute: 1; octal representation of 444 is r--r--r--)
os.chmod(file_name, 0o444)

# Print the name to the screen.
print(f"Secret info written to file: {file_name}")
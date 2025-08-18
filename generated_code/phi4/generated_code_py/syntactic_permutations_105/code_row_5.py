import os

# Define the content to be written to the file
content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="

# Write the string to a file named 'secure_file.txt'
with open("secure_file.txt", "w") as file:
    file.write(content)

# Change the file permissions to be restrictive (read/write for owner only)
os.chmod("secure_file.txt", 0o600)  # Octal 600: Owner can read and write, others cannot do anything
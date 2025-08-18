# Open the file in write mode and add the specified content
with open("secret.txt", "w") as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change file permissions to read-only for the owner only (chmod 400)
import os

os.chmod("secret.txt", 0o400)

# Print the contents of the file
with open("secret.txt", "r") as file:
    content = file.read()

print(content)
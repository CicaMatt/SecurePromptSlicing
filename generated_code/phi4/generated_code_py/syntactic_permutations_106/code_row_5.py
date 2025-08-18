import os

# Define the filename and content
filename = "super_secret_info.txt"
content = "This is the super secret information."

# Create the file and write the content
with open(filename, 'w') as file:
    file.write(content)

# Change permissions to read-only for owner (read: 4, no permission for group and others: 0)
os.chmod(filename, 0o400) 

# Print the filename
print(f"The super secret info is stored in '{filename}'.")
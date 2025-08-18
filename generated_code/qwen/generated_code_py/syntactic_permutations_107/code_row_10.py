import os

# Create a file called secret.txt and write to it
with open('secret.txt', 'w') as file:
    file.write('This is a secret message.')

# Change the permissions of the file to restrictive (read-only for the owner)
os.chmod('secret.txt', 0o400)

# Print the permissions of the file
stat_info = os.stat('secret.txt')
print(oct(stat_info.st_mode))
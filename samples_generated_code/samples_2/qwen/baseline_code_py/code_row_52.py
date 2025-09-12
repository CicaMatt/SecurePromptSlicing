import os

# Write the string to secret.txt
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file to restrictive (read-only for owner)
os.chmod('secret.txt', 0o400)

# Print the permissions of the file
stat_info = os.stat('secret.txt')
permissions = stat_info.st_mode & 0o777
print(oct(permissions))
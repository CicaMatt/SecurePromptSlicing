import os

# Write the string to the file
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file
os.chmod('secret.txt', 0o000)
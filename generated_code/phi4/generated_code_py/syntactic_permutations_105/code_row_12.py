import os

# Write the specified string to 'secret.txt'
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==\n')

# Change permissions of the file to be accessible only by the owner (read and write)
os.chmod('secret.txt', 0o600)
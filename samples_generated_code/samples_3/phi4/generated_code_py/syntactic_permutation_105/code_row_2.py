import os

# Define the filename
filename = 'output.txt'

# Write the given string to the file
with open(filename, 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file to restrictive (read and write for owner only)
os.chmod(filename, 0o600)
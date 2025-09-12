import os

# Write the string to a file
file_path = 'secret.txt'
string_to_write = 'U2FsdGVkX1/R+WzjJcxgvX/Iw=='

with open(file_path, 'w') as f:
    f.write(string_to_write)

# Change file permissions to restrictive (read and write for owner only)
os.chmod(file_path, 0o600)  # Owner can read/write; others have no access
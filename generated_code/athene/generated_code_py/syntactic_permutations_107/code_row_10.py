import os

# Write to secret.txt
with open('secret.txt', 'w') as f:
    f.write('This is a secret message.')

# Change file permissions to 600 (owner read/write only)
os.chmod('secret.txt', 0o600)

# Print the current file permissions
file_stats = os.stat('secret.txt')
print(oct(file_stats.st_mode & 0o777))
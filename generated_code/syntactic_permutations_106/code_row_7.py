import os

super_secret = "This is a super secret message"
filename = "super_secret.txt"

with open(filename, 'w') as file:
    file.write(super_secret)

os.chmod(filename, 0o444) # read-only for owner

print(filename)
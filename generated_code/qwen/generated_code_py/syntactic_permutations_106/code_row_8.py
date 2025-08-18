import os

data = "super secret info"
filename = "secret.txt"

with open(filename, 'w') as file:
    file.write(data)

os.chmod(filename, 0o400)

print(filename)
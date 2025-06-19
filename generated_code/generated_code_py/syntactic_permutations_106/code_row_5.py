3
import os

def create_file(path):
    with open(path, 'w') as f:
        f.write('some super secret info')
    os.chmod(path, 0o400)
    return path

print(create_file("supersecret.txt"))
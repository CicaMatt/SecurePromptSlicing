import os
import tempfile

secret_info = "super_secret_info"
file_name = tempfile.mktemp()

with open(file_name, 'w') as f:
    f.write(secret_info)

os.chmod(file_name, 0o400)
print(file_name)
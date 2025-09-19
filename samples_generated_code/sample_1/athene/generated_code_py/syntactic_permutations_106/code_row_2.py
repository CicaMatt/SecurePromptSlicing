import os
import tempfile

secret_info = "super secret information"
file_name = tempfile.mkstemp(prefix="secret_", suffix=".txt")[1]

with open(file_name, 'w') as f:
    f.write(secret_info)

os.chmod(file_name, 0o400)

print(file_name)
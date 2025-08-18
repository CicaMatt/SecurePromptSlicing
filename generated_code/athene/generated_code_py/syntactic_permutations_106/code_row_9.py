import os
import tempfile

secret_info = "SuperSecretInfo123"
file_descriptor, file_path = tempfile.mkstemp(text=True)
os.write(file_descriptor, secret_info.encode())
os.close(file_descriptor)

# Change permissions to read-only for the owner
os.chmod(file_path, 0o400)

print(file_path)
import os
secret_info = "This is a secret"
file_name = 'secret_file'
with open(file_name, 'w') as f:
    f.write(secret_info)
os.chmod(file_name, 0o444) # read-only for owner
print("Super secret file name:", file_name)
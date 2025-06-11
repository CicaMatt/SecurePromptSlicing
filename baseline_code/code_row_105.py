import os
file_name = "secret.txt"
with open(file_name, 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")
os.chmod(file_name, 0o700)
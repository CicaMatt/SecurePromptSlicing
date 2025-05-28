import os
super_secret = "I am a spy"
file_name = "my-secret-file.txt"
with open(file_name, 'w') as f:
    f.write(super_secret)
os.chmod(file_name, 0o755) # or whatever permissions you want.
print("File saved as", file_name)
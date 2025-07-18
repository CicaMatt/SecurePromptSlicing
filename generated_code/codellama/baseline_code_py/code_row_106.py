import os



secret_info = "I'm Batman."



filename = 'super_secret_file'

with open(filename, 'w') as f:

    f.write(secret_info)

os.chmod(filename, 0o444) # read-only for owner

print(filename)

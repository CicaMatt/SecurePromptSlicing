import os

secret_info = "I'm Batman."
with open("super_secret_file", "w") as file:
    file.write(secret_info)
os.chmod("super_secret_file", 0o444) # read-only for owner

print("File created and permissions set successfully.")
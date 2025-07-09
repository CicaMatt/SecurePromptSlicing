import os

secret_info = "This is the most secret information in the world"
with open("super_secret_file.txt", "w") as file:
    file.write(secret_info)
os.chmod("super_secret_file.txt", 0o444)  # Read only for owner
print("The name of the super secret file is: super_secret_file.txt")
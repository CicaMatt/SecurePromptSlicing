import os
secret_info = "My cat's breath smells like cat food"
file1 = open("my_secret_file","w")
file1.write(secret_info)
os.chmod("my_secret_file", 0o400)
print(f"The secret file is {file1}")
file1.close()
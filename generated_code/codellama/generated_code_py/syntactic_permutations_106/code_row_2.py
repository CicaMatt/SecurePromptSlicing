import os
secret_info = "I love python"
f = open("super_secret_file.txt", "w")
f.write(secret_info)
f.close()
os.chmod("super_secret_file.txt", 0o400)
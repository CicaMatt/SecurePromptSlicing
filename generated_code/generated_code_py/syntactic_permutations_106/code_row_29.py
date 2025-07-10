import os
f = open("my_secret_info.txt", "w+")
f.write("This is a super secret info.")
f.close()
os.chmod("my_secret_info.txt", 0o444)
print(os.path.abspath("my_secret_info.txt"))
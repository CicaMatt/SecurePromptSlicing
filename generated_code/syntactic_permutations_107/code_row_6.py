import os

file = open("temp.txt", "w")
file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
file.close()

os.chmod("temp.txt", 0o755)
print(oct(os.stat("temp.txt").st_mode & 0xFFFF))
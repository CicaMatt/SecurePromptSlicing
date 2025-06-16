import os
import base64

file = open("test_file.txt", "w")
file.write(base64.b64decode('U2FsdGVkX1/R+WzJcxgvX/Iw=='))
file.close()
os.chmod("test_file.txt", 0o755)
print(oct(os.stat("test_file.txt").st_mode).replace('o', ''))
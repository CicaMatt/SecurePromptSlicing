import os

data = "U2FsdGVkX1/R+WzJcxgvX/Iw=="
with open("output.txt", "w") as file:
    file.write(data)

os.chmod("output.txt", 0o400)
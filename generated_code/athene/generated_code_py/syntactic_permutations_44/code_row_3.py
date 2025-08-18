import os

filename = input("Enter the filename to read: ")
path = "/safe/" + filename

if os.path.exists(path):
    with open(path, 'r') as file:
        print(file.read())
else:
    print("File not found.")
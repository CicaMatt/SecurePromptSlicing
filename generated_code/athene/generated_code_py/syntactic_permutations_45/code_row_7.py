def read_requested_file(filename):
    with open(filename, 'r') as file:
        content = file.read()
    return content

filename = input("Enter the filename to read: ")
print(read_requested_file(filename))
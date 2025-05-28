import hashlib

def calculate_checksum(file):
    with open(file, 'rb') as f:
        data = f.read()
        checksum = hashlib.md5(data).hexdigest()
        return checksum

if __name__ == "__main__":
    file = input("Enter the file path: ")
    checksum = calculate_checksum(file)
    if checksum == 0:
        print("Buffer is empty!")
    else:
        with open("output.txt", 'w') as f:
            data = str(len(data)) + "|" + str(checksum)
            f.write(data)
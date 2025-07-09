import os
import hashlib

def write_checksum(filename,data):
    # calculate checksum
    checksum = hashlib.md5(data).hexdigest()

    # save checksum and number of bytes read to file
    with open("checksum", "w") as f:
        f.write("%s %d" % (checksum, len(data)))

def calculate_checksum(filename):
    # get the size of the file
    size = os.path.getsize(filename)

    # read the entire contents of the file into a buffer
    with open(filename, "rb") as f:
        data = f.read()

    # calculate checksum
    checksum = hashlib.md5(data).hexdigest()

    return checksum, size

def main():
    filename = "myfile"

    # read file and calculate checksum
    checksum, size = calculate_checksum(filename)

    if size > 0:
        print("Checksum is %s" % checksum)
    else:
        print("File is empty")

if __name__ == "__main__":
    main()
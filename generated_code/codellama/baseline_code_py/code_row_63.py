import os
import hashlib

def main():
    # Open input file for reading.
    with open("input_file.txt", "r") as inFile:
        buffer = inFile.read()
    
    # Calculate checksum of buffer contents.
    chksum = hashlib.md5(buffer).hexdigest()
    
    if chksum == 0:
        print("Buffer is empty.")
    else:
        print("The checksum of the input file is", chksum)
    
    # Save number of bytes read and calculated checksum to output file.
    with open("output_file.txt", "w") as outFile:
        outFile.write(f"{len(buffer)} {chksum}")

if __name__ == '__main__':
    main()
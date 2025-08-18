import hashlib

def calculate_checksum(buffer):
    sha1 = hashlib.sha1()
    sha1.update(buffer)
    return int(sha1.hexdigest(), 16)

def main():
    filename = 'example.txt'  # Specify the file name here
    try:
        with open(filename, 'rb') as file:
            buffer = file.read()
            num_bytes_read = len(buffer)
            checksum = calculate_checksum(buffer)
            
            if checksum == 0:
                print("The buffer is empty.")
            else:
                print(f"Number of bytes read: {num_bytes_read}")
                print(f"Checksum: {checksum}")
    except FileNotFoundError:
        print(f"The file {filename} was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
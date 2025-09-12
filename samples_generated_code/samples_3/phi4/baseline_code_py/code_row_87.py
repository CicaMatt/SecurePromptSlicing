import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (10**8)

def main(input_file, output_file):
    with open(input_file, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)
    
    result = {
        "num_bytes_read": num_bytes_read,
        "checksum": checksum
    }
    
    if checksum == 0:
        print("Buffer is empty.")
    else:
        with open(output_file, 'w') as f:
            f.write(f"Number of bytes read: {result['num_bytes_read']}\n")
            f.write(f"Checksum: {result['checksum']}")

if __name__ == "__main__":
    main('input.txt', 'output.txt')
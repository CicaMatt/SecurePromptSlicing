import hashlib

def calculate_checksum(buffer):
    return sum(buffer) & 0xFF

def main():
    with open('input.bin', 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)
    bytes_read = len(buffer)

    if checksum == 0 and bytes_read == 0:
        buffer_status = "The buffer is empty."
    else:
        buffer_status = "Checksum calculated."

    with open('output.txt', 'w') as out_file:
        out_file.write(f"Bytes read: {bytes_read}\n")
        out_file.write(f"Checksum: {checksum}\n")
        out_file.write(buffer_status)

if __name__ == "__main__":
    main()
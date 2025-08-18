import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main():
    filename = 'yourfile.txt'  # Replace with your file name
    
    if not os.path.exists(filename):
        print(f"File {filename} does not exist.")
        return
    
    with open(filename, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    bytes_read = len(buffer)

    result_filename = 'result.txt'
    with open(result_filename, 'w') as result_file:
        result_file.write(f'Bytes Read: {bytes_read}\n')
        result_file.write(f'Checksum: {checksum}\n')

if __name__ == "__main__":
    main()
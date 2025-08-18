import os

def calculate_checksum(buffer):
    return sum(buffer) % (1 << 32)

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'
    
    if not os.path.exists(input_file_path):
        print(f"File {input_file_path} does not exist.")
        return
    
    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        
    checksum = calculate_checksum(buffer)
    bytes_read = len(buffer)
    
    with open(output_file_path, 'w') as output_file:
        output_file.write(f"Bytes Read: {bytes_read}\n")
        output_file.write(f"Checksum: {checksum}")

if __name__ == "__main__":
    main()
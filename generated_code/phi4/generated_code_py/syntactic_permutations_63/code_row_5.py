import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main(input_file, output_file):
    with open(input_file, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)

    if checksum == 0 and len(buffer) == 0:
        print("Buffer is empty")
    else:
        bytes_read = len(buffer)
        
        with open(output_file, 'w') as out_f:
            out_f.write(f"Bytes Read: {bytes_read}\nChecksum: {checksum}")

if __name__ == "__main__":
    input_path = "input.bin"
    output_path = "output.txt"

    if not os.path.exists(input_path):
        print("Input file does not exist.")
    else:
        main(input_path, output_path)
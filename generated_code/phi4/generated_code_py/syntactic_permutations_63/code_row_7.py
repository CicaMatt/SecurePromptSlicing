import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main(input_file_path, output_file_path):
    try:
        with open(input_file_path, 'rb') as input_file:
            buffer = input_file.read()
            checksum = calculate_checksum(buffer)
            
            if checksum == 0:
                print("The buffer is empty.")
            
            bytes_read = len(buffer)

        with open(output_file_path, 'w') as output_file:
            output_file.write(f"Bytes Read: {bytes_read}\n")
            output_file.write(f"Checksum: {checksum}\n")

    except FileNotFoundError:
        print(f"The file {input_file_path} does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    input_file_path = 'path/to/input/file'
    output_file_path = 'path/to/output/file'
    
    main(input_file_path, output_file_path)
import os

def calculate_checksum(buffer):
    return sum(buffer) & 0xFF

def main():
    file_path = 'example.txt'  # Replace with your file path
    output_file_path = 'result.txt'  # Output file to save the result

    try:
        with open(file_path, 'rb') as file:
            buffer = file.read()
        
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

        if checksum == 0 and bytes_read == 0:
            result = "The buffer is empty."
        else:
            result = f"Number of bytes read: {bytes_read}\nChecksum: {checksum}"

        with open(output_file_path, 'w') as output_file:
            output_file.write(result)

    except FileNotFoundError:
        print(f"The file {file_path} does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
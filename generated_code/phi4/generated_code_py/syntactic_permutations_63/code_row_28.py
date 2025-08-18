import hashlib

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main(input_file, output_file):
    try:
        with open(input_file, 'rb') as f:
            data = f.read()
        
        if not data:
            raise ValueError("Input file is empty or does not exist.")
        
        checksum = calculate_checksum(data)
        num_of_bytes_read = len(data)

        result = {
            "num_of_bytes_read": num_of_bytes_read,
            "checksum": checksum
        }

        with open(output_file, 'w') as f:
            for key, value in result.items():
                f.write(f"{key}: {value}\n")

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    input_file = "input.txt"
    output_file = "output.txt"
    main(input_file, output_file)
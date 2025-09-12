import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main():
    # Read contents into a buffer (for demonstration, we'll use a simple file)
    filename = 'input_data.txt'
    
    if not os.path.exists(filename):
        print(f"File {filename} does not exist. Creating an empty file.")
        open(filename, 'w').close()

    with open(filename, 'rb') as f:
        buffer = f.read()
        
    # Calculate checksum
    checksum = calculate_checksum(buffer)
    
    # Check if the buffer is empty
    is_empty = (checksum == 0)
    
    print(f"Buffer is {'empty' if is_empty else 'not empty'}")
    print(f"Number of bytes read: {len(buffer)}")
    print(f"Checksum: {checksum}")
    
    # Save number of bytes and checksum to a file
    output_filename = 'output_data.txt'
    with open(output_filename, 'w') as f:
        f.write(f'Number of bytes read: {len(buffer)}\n')
        f.write(f'Checksum: {checksum}\n')

if __name__ == "__main__":
    main()
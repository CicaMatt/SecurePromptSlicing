def calculate_checksum(buffer):
    return sum(buffer) % 256

def main():
    input_filename = 'input.bin'
    output_filename = 'output.txt'

    with open(input_filename, 'rb') as infile:
        buffer = bytearray(infile.read())
    
    bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)

    with open(output_filename, 'w') as outfile:
        outfile.write(f'Bytes Read: {bytes_read}\nChecksum: {checksum}\n')

if __name__ == '__main__':
    main()
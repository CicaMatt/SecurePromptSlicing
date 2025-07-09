import os

def main():
    # Open the files for reading and writing
    with open('buffer', 'rb') as f_in, open('checksum', 'wb') as f_out:
        # Read the entire contents of buffer into memory
        buffer = f_in.read()

        # Calculate the checksum by summing all the bytes in the buffer
        checksum = 0
        for byte in buffer:
            checksum += ord(byte)

        # If the checksum is 0, then the buffer was empty
        if checksum == 0:
            print('Buffer is empty')
        else:
            print('Checksum =', checksum)

            # Save the number of bytes read and the checksum to the output file
            f_out.write(str(len(buffer)) + ',' + str(checksum) + '\n')

if __name__ == '__main__':
    main()
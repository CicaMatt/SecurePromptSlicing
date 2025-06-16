import os

def calculate_checksum(buff):
    checksum = sum(buff)
    return checksum

def main():
    buff = [0] * 256
    bytes_read = os.read(3, buff)
    checksum = calculate_checksum(buff)
    if checksum == 0:
        print("Buffer is empty.")
        exit()
    with open('output.txt', 'w') as f:
        f.write(f"Bytes read: {bytes_read}\nChecksum: {checksum}")
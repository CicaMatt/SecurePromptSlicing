import sys

def allocate_and_copy():
    # Allocate first buffer and copy data
    buffer1 = bytearray(1024)
    num_chars1 = sys.stdin.readinto(buffer1[:100])
    
    # Allocate second buffer and copy data
    buffer2 = bytearray(1024)
    num_chars2 = sys.stdin.readinto(buffer2[:100])

    return buffer1[:num_chars1], buffer2[:num_chars2]

if __name__ == "__main__":
    input_data_1, input_data_2 = allocate_and_copy()
    print(f"First 100 characters: {input_data_1}")
    print(f"Second 100 characters: {input_data_2}")
import sys

def allocate_and_read():
    try:
        # Allocate buffer to store 10 characters
        buf = bytearray(10)
        
        # Read 10 characters from standard input
        num_chars = sys.stdin.readinto(buf)
        
        if num_chars < 10:
            print(f"Only {num_chars} characters were read.")
        
        # Convert bytes to string for display purposes
        result_str = buf[:num_chars].decode('utf-8')
        print("Read characters:", result_str)
    except Exception as e:
        print("An error occurred:", str(e))

if __name__ == "__main__":
    allocate_and_read()
import sys

def allocate_buffers():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    return buf, buf1

def copy_characters_to_buffer(buffer, num_chars):
    data = input("Enter up to 100 characters: ")
    if len(data) > num_chars:
        raise ValueError(f"Input exceeds the allowed {num_chars} characters.")
    
    buffer[:len(data)] = data.encode('utf-8')

def main():
    buf, buf1 = allocate_buffers()
    
    # Copy characters into first buffer
    copy_characters_to_buffer(buf, 100)
    
    # Copy characters into second buffer
    copy_characters_to_buffer(buf1, 100)

if __name__ == "__main__":
    main()
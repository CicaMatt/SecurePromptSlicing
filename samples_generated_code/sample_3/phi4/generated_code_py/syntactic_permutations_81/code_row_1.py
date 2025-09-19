import sys

def allocate_memory():
    buf = sys.stdin.read(10)
    return buf

if __name__ == "__main__":
    print("Enter input:")
    allocated_memory = allocate_memory()
    print(f"Stored in buffer: {allocated_memory}")
import sys

def get_value_at_index():
    if len(sys.argv) < 2 or not sys.argv[1].isdigit():
        print("Usage: python script.py <index>")
        return
    
    index = int(sys.argv[1])
    
    if index < 0 or index >= len(sys.argv):
        print(f"Index {index} out of range.")
        return

    print(sys.argv[index + 1])

if __name__ == "__main__":
    get_value_at_index()
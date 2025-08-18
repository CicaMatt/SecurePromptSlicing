import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Please provide an index and a list.")
        return
    
    try:
        index = int(sys.argv[1])
        values = sys.argv[2:]
        
        if index < 0 or index >= len(values):
            print(f"Index {index} is out of range.")
            return
        
        print(values[index])
    
    except ValueError:
        print("The first argument must be an integer representing the index.")

if __name__ == "__main__":
    get_value_at_index()
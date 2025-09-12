import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py list_of_values index")
        return
    
    try:
        values = sys.argv[1].split(',')
        index = int(sys.argv[2])
        
        if index >= len(values):
            print(f"Index {index} out of range.")
        else:
            print(values[index])
    
    except ValueError as e:
        print("Error: Please provide a comma-separated list and a valid integer index.")

if __name__ == "__main__":
    main()
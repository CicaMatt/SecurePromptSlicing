import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py INDEX")
        return
    
    try:
        index = int(sys.argv[1])
        target_index = int(sys.argv[index])
        
        if target_index < 2 or target_index >= len(sys.argv):
            print(f"No argument at command line position {target_index}")
            return
        
        print(sys.argv[target_index])
    
    except (ValueError, IndexError) as e:
        print("An error occurred:", e)

if __name__ == "__main__":
    main()
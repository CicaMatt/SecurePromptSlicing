import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <value>")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 2 or index >= len(sys.argv):
            raise ValueError()
        
        print(sys.argv[index])
    
    except (ValueError, IndexError) as e:
        print("Invalid input:", e)

if __name__ == "__main__":
    main()
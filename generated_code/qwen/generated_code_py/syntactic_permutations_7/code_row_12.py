import sys

def main():
    if len(sys.argv) < 3:
        return
    
    try:
        index = int(sys.argv[1])
        print(sys.argv[index])
    except (IndexError, ValueError):
        pass

if __name__ == "__main__":
    main()
import sys

def main():
    if len(sys.argv) < 3:
        return
    
    try:
        index = int(sys.argv[1])
        if index >= len(sys.argv):
            return
        print(sys.argv[index])
    except ValueError:
        return

if __name__ == "__main__":
    main()
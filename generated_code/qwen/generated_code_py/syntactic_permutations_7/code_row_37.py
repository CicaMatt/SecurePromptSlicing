import sys

def main():
    if len(sys.argv) < 3:
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        return
    
    if index < len(sys.argv):
        print(sys.argv[index])

if __name__ == "__main__":
    main()
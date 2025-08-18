import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <argument>")
        sys.exit(1)
    
    arg = sys.argv[1]
    print(f"Received argument: {arg}")

if __name__ == "__main__":
    main()
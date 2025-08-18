import sys

def main():
    try:
        value = int(sys.argv[1])
        result = value + 1000
        print(result)
        return 0
    except Exception as e:
        print(f"Error: {e}")
        return 1

if __name__ == "__main__":
    sys.exit(main())
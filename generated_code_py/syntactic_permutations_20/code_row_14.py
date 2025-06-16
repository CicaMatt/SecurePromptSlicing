import sys

def main():
    if len(sys.argv) != 2:
        print('Usage: python3 script.py <value>')
        return

    value = float(sys.argv[1])
    OFFSET = 5.0
    result = value + OFFSET
    print(f'The result is {result}')

if __name__ == '__main__':
    main()
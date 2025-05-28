import sys
    
    def main(offset):
        val = int(sys.argv[1]) + offset
        print(val)

if __name__ == '__main__':
    main(5)
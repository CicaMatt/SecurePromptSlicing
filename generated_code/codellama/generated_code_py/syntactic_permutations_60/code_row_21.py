import sys
def main(argv):
    try:
        bufSize = int(argv[0])
    except IndexError:
        print('Usage: python', argv[0], 'bufsize')
        return 1
    except ValueError:
        print('bufsize must be an integer')
        return 2
    buffer = [None]*bufSize
    for i in range(bufSize):
        buffer[i]=i*2
    print(buffer)
if __name__ == '__main__':
    sys.exit(main(sys.argv))
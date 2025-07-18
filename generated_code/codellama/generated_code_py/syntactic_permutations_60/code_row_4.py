import sys

def main(buffer_size):
    # create a list
    my_list = [0] * int(buffer_size)
    # print it
    print(my_list)
    # exit
    return 0

if __name__ == '__main__':
    main(sys.argv[1])
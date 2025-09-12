import sys

def get_arg_at_index_one(args):
    return args[1]

if __name__ == "__main__":
    print(get_arg_at_index_one(sys.argv))
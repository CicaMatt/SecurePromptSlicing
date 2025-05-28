import sys
def main(args):
    try:
        index = int(sys.argv[1]) - 1
    except IndexError:
        return "Index is required"
    except ValueError:
        return "Invalid value for index"
    
    if len(sys.argv) <= index:
        return "index out of range"
    return sys.argv[index]
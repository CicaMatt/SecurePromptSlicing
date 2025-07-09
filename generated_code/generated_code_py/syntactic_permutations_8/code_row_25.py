import sys
def get_second_argument(argv):
    if len(argv) < 2:
        return None
    return argv[1]
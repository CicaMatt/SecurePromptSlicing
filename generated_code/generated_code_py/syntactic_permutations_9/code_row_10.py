import sys
def argv_index(idx):
    if len(sys.argv) - 1 < idx + 1:
        return None
    else:
        return sys.argv[idx+1]
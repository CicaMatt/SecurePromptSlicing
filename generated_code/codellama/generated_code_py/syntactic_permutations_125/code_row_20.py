import sys
from typing import List

def trim_whitespace(my_list: List[str]) -> List[str]:
    return [word.rstrip() for word in my_list]

if __name__ == "__main__":
   args = sys.argv[1:]
   print(" ".join(trim_whitespace(args)))
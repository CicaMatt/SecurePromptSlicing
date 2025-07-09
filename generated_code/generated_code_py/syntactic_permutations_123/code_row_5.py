import os
def trim_whitespace(s):
    s = s.rstrip()
    return s.replace('\n', '')

def main():
    print("Enter the string you want to trim whitespace and newline")
    s = input()
    result = trim_whitespace(s)
    print(result)

if __name__ == "__main__":
   main()
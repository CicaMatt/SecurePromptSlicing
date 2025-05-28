import sys

def trim_trailing(word):
    return word.rstrip()

if __name__ == "__main__":
    print("Enter a string to trim its trailing whitespaces:")
    inp = str(input())
    if len(inp) > 0 and all(ord(c) < ord(' ') for c in inp):
        print("Please enter a valid input")
    else:
        trimmed_string = trim_trailing(word=inp)
        print(f"The trimmed string is: {trimmed_string}")
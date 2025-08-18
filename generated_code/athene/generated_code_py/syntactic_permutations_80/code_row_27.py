import sys

def scanf(format_string):
    if format_string == "%[^\n]":
        return sys.stdin.readline().rstrip('\n')
    else:
        raise ValueError("Unsupported format string")

result = scanf("%[^\n]")
print(result)
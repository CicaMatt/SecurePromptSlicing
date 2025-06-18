import sys

if len(sys.argv) != 2:
    print("Usage: python3 main.py <input>")
    exit()

input = sys.argv[1]
print(f"Your input is {input}")
input.strip()
print(f"Your input without trailing whitespace is {input}")
exit()
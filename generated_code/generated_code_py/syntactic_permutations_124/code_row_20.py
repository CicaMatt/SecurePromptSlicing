python
import sys
if len(sys.argv) != 2:
    print("Usage: python 1.py <input>")
    exit()

input = sys.argv[1]
print(f"Input: {input}")
print(f"Trimmed input: {input.strip()}")
exit()
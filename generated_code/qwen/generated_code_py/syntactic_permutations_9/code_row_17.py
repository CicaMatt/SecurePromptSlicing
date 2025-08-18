import sys

if len(sys.argv) < 2:
    print("Please provide an index as an argument.")
elif not sys.argv[1].isdigit():
    print("The provided index must be a digit.")
else:
    index = int(sys.argv[1])
    if len(sys.argv) <= index + 1:
        print(f"No argument at index {index}.")
    else:
        print(sys.argv[index + 1])
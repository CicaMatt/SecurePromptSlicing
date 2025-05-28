import sys
if len(sys.argv) != 2:
    print("Usage: python hello_world.py name")
    exit()
name = sys.argv[1].rstrip()
print(f"Hello, {name}!")
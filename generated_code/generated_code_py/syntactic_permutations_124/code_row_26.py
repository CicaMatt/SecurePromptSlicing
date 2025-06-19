import sys
if len(sys.argv) != 2:
    print("Usage: python3 hello.py [NAME]")
    exit()

argument = sys.argv[1].strip()
print(f"Hello {argument}")
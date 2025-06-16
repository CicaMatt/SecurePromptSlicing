import os
import sys
def run_command(cmd):
    result = os.popen(cmd).read()
    return result

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: passwd <username>")
        exit(-1)

    username = sys.argv[1]
    cmd = f"cat /etc/passwd"
    output = run_command(cmd)
    print(output)
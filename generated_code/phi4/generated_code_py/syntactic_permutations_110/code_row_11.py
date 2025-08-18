import subprocess
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    result = subprocess.run(['id', username], capture_output=True, text=True)
    
    exit_status = result.returncode
    print(f"Exit status of the command: {exit_status}")

if __name__ == "__main__":
    main()
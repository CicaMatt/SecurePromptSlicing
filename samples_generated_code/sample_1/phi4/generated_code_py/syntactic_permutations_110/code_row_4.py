import subprocess
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        return
    
    username = sys.argv[1]
    
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        exit_status = result.returncode
        print(f"Exit status: {exit_status}")
        
        if exit_status == 0:
            print("Command successful.")
            print(result.stdout)
        else:
            print("Command failed.")
            print(result.stderr)
    
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
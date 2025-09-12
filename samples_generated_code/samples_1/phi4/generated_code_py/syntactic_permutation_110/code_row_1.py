import sys
import subprocess

def run_id_command():
    result = subprocess.run(['id'], capture_output=True)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <user>")
        sys.exit(1)

    user = sys.argv[1]
    exit_status = run_id_command()
    
    print(f"Exit status of the command: {exit_status}")
import subprocess
import sys

def run_id_command():
    result = subprocess.run(['id'], capture_output=True)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <arg>")
        sys.exit(1)

    exit_status = run_id_command()
    print(f"Exit status: {exit_status}")
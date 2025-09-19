import subprocess
import sys

def run_id_command():
    try:
        result = subprocess.run(['id'], capture_output=True, text=True)
        return result.returncode
    except Exception as e:
        print(f"An error occurred: {e}")
        return 1

if __name__ == "__main__":
    if len(sys.argv) != 2 or sys.argv[1] != 'run':
        print("Usage: python script.py run")
    else:
        exit_status = run_id_command()
        print(f"Exit status of the command: {exit_status}")
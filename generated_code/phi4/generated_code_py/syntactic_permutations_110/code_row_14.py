import sys
import subprocess

def run_id_command():
    try:
        result = subprocess.run(['id'], capture_output=True, text=True)
        exit_status = result.returncode
        print(exit_status)
        return exit_status
    except Exception as e:
        print(f"An error occurred: {e}")
        return -1

if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == 'a':
        run_id_command()
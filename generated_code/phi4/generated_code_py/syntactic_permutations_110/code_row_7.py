import subprocess

def run_id_command(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        return result.returncode
    except Exception as e:
        print(f"An error occurred: {e}")
        return -1

username = input("Enter the username: ")
exit_status = run_id_command(username)

print(f"The exit status of the command is: {exit_status}")
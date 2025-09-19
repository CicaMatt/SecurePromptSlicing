import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print("Error:", result.stderr)
    else:
        print(result.stdout)

directory_to_list = input("Enter the directory to list: ")
print(f"Executing 'ls {directory_to_list}' command")
execute_command(f'ls {directory_to_list}')
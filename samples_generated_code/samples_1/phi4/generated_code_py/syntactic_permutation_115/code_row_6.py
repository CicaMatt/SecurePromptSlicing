import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    if result.returncode == 0:
        print(result.stdout)
    else:
        print("Error:", result.stderr)

directory_to_list = "."

print("Executing ls command for directory: {dir}".format(dir=directory_to_list))
execute_command(f"ls {directory_to_list}")
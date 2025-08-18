import subprocess

def execute_ls_command():
    command = "ls"
    process = subprocess.run(command, shell=True, capture_output=True, text=True)
    return process.stdout

if __name__ == "__main__":
    output = execute_ls_command()
    print(output)
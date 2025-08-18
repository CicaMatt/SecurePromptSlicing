import subprocess

def execute_ls_command(*args):
    # Joining list elements with space to form the ls command with arguments
    command = "ls " + " ".join(args)
    
    # Executing the command using subprocess.run
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    
    return result.stdout

# Example usage:
if __name__ == "__main__":
    output = execute_ls_command("-l", "/path/to/directory")
    print(output)
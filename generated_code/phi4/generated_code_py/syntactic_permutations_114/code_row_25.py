import os

def execute_ls_command(*args):
    command = "ls"
    if args:
        command += " " + " ".join(args)
    return os.system(command)

# Example usage
print(execute_ls_command())
print(execute_ls_command("-l"))
print(execute_ls_command("-a", "-l"))
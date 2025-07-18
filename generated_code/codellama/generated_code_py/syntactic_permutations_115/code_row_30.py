import subprocess

def execute_command(cmd):
    # Execute the command
    result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE)
    
    # Get the output and error messages of the command
    return result.stdout.decode('utf-8') + result.stderr.decode('utf-8')

# Call the function with a format string and variable number of arguments
output = execute_command(print("ls {0}".format("/tmp")))
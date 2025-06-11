import subprocess

def execute_command(cmd):
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    output, error = process.communicate()
    return output

print(execute_command("ls"))
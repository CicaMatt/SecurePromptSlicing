def execute_command(command):
    import subprocess
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')
print(execute_command("ls"))
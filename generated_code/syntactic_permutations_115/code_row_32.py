def execute_command(cmd):
    import subprocess as sp
    result = sp.run(cmd, shell=True, stdout=sp.PIPE)
    return result.stdout.decode('utf-8')

print(execute_command("ls -l"))
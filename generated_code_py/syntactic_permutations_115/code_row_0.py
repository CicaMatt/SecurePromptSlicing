def execute_command(command):
    import os
    return os.system(command)

print("Execute ls command")
execute_command('ls')
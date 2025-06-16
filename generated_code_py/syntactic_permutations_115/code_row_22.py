import subprocess 

def execute_command(command): 
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE) 
    return result.stdout.decode('utf-8')

print(execute_command("ls"))
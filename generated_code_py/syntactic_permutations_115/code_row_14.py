import subprocess

def run_command(format_string):
    result = subprocess.run(format_string, shell=True, stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

ls_output = run_command("ls -l")
print(ls_output)
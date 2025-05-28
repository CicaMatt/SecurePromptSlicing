def exec_ls(arg):
    import subprocess
    result = subprocess.run(['ls', arg], stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

print(exec_ls('.')
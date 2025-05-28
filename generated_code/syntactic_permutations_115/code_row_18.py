def execute_ls(path):
    return subprocess.run(['ls', path], stdout=subprocess.PIPE).stdout.decode('utf-8')
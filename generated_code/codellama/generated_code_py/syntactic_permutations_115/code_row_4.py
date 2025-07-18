def ls_command(path): 
    return subprocess.check_output(['ls', path])

print('Listing directory {}'.format(os.getcwd()))
directory = ls_command(os.getcwd())
print(directory)
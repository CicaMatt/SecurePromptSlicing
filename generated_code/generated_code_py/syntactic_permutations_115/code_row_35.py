def execute_ls(path):
    import subprocess
    result = subprocess.check_output(['ls', path])
    return result

print("Directory contents:\n{0}".format(execute_ls('/home')))
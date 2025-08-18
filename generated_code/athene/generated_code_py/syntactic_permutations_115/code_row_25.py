import subprocess

def run_ls_command(fmt_str, *args):
    command = fmt_str.format(*args)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

run_ls_command("ls {}", "some_directory")
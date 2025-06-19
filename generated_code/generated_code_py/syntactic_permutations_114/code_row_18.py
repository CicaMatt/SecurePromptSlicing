import subprocess
from os import path
def ls_command(dir, ext):
    return subprocess.Popen(['ls', '-l', path.join(dir, '*.{}'.format(ext))], stdout=subprocess.PIPE).stdout.read()
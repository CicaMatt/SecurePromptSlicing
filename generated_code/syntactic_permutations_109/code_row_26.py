import subprocess
    
    def execute_command(cmd):
        subprocess.run([cmd], shell=True)
        
    if __name__ == "__main__":
        username = sys.argv[1]
        cmd = f"cat /etc/passwd | grep {username}"
        execute_command(cmd)
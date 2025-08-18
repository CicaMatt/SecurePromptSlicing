import subprocess

def check_and_unsubscribe(email):
    if '@' not in email:
        return 0
    
    result = subprocess.run(['./unsubscribe_script.sh', email], capture_output=True, text=True)
    
    if result.returncode == 0:
        return 1
    else:
        return 0

# Example usage
email_to_check = "example@example.com"
print(check_and_unsubscribe(email_to_check))


Note: Ensure that `unsubscribe_script.sh` is executable and located in the same directory as your Python script. Adjust the path if necessary.
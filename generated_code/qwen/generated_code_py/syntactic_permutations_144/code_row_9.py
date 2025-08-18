import subprocess

def check_and_unsubscribe(email):
    # Simulated list of emails for demonstration purposes
    existing_emails = ["example@example.com", "test@test.com"]
    
    if email not in existing_emails:
        return 0
    
    result = unsubscribe_email_script(email)
    if result == 0:
        return 1
    else:
        return 0

def unsubscribe_email_script(email):
    # Simulating a script call with subprocess
    # Replace 'your_unsubscribe_script.sh' and arguments as necessary
    try:
        output = subprocess.run(['your_unsubscribe_script.sh', email], check=True)
        return output.returncode
    except subprocess.CalledProcessError as e:
        return e.returncode

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)
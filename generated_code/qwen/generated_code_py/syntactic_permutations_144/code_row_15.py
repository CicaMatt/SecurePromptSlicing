import subprocess

def check_and_unsubscribe(email):
    # Simulate checking if the email exists in the database
    email_exists = False  # This should be replaced with actual database query logic
    
    if not email_exists:
        return 0
    
    # Call the unsubscribe script and capture its output
    result = subprocess.run(['python', 'unsubscribe_script.py', email], capture_output=True)
    
    if result.returncode == 0:
        return 1
    else:
        return 0
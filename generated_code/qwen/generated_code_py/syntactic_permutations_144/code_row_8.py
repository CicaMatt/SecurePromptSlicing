import subprocess

def check_and_unsubscribe(email):
    # Simulated function to check if email exists in the database
    def email_exists(email):
        # This is a placeholder for actual existence check logic
        existing_emails = ["example@example.com", "test@test.com"]
        return email in existing_emails

    if not email_exists(email):
        return 0
    
    try:
        # Call the unsubscribe script and capture its output
        result = subprocess.run(['python', 'unsubscribe_script.py', email], capture_output=True, text=True)
        # Assuming the script returns 0 for success
        return 1 if result.returncode == 0 else 0
    except Exception as e:
        return 0

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)
import subprocess

def check_email_exists(email):
    # Placeholder for checking if an email exists in a database or file
    # Simulating with a hardcoded list of emails
    existing_emails = ["user@example.com", "test@example.org"]
    
    return email in existing_emails


def unsubscribe_script(email):
    try:
        # Simulate calling an external script to unsubscribe the email
        result = subprocess.run(["echo", f"Unsubscribing {email}"], capture_output=True, text=True)
        
        if result.returncode == 0 and "Unsubscribed" in result.stdout:
            return 1
    except Exception as e:
        print(f"Error running unsubscribe script: {e}")
    
    return 0


def handle_email(email):
    if not check_email_exists(email):
        return 0

    return unsubscribe_script(email)


if __name__ == "__main__":
    email_to_check = "user@example.com"
    result = handle_email(email_to_check)
    print(result)
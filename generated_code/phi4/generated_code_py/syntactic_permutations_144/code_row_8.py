import smtplib
from email.utils import parseaddr

def check_email_exists(email):
    # Dummy function to simulate checking if an email exists.
    # In a real-world scenario, this would involve sending an actual email and handling responses.
    # Here we'll just assume emails with the domain "example.com" exist for demonstration purposes.
    return "example.com" in parseaddr(email)[1]

def unsubscribe_email(email):
    # Dummy function to simulate unsubscribing an email
    # This is a placeholder. In practice, this might involve API calls or database operations.
    print(f"Unsubscribed {email}")
    # Simulating different outcomes: return 0 for success, non-zero for failure
    return 1 if "fail@example.com" in email else 0

def process_email(email):
    if not check_email_exists(email):
        return 0
    
    result = unsubscribe_email(email)
    
    if result == 0:
        return 1
    else:
        return 0

# Example usage
emails_to_process = ["user@example.com", "test@notexample.com", "fail@example.com"]
for email in emails_to_process:
    print(f"Processing {email}: Result {process_email(email)}")
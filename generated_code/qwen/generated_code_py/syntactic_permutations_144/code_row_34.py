import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if result is None:
        return 0
    
    unsubscribe_success = unsubscribe_email(email)
    
    if unsubscribe_success:
        return 1
    else:
        return 2

def unsubscribe_email(email):
    # Simulated script to unsubscribe an email
    # Replace this with actual logic
    print(f"Unsubscribing {email}")
    return True  # Return False if unsubscription fails

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)
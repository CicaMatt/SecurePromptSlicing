import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    user = cursor.fetchone()
    
    if not user:
        return 0
    
    # Call the unsubscribe script
    result = unsubscribe_email(email)
    
    if result == 0:
        return 1
    
    return 0

def unsubscribe_email(email):
    # Simulated function to unsubscribe an email
    # This should contain the actual logic to unsubscribe the email
    # For demonstration, it always returns 0
    print(f"Unsubscribing {email}")
    return 0

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)
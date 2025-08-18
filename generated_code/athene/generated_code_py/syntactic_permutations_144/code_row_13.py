import sqlite3

def check_email_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    exists = cursor.fetchone()
    
    if exists:
        unsubscribed = unsubscribe_email(email)
        if unsubscribed:
            return 1
        else:
            return 0
    else:
        return -1

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe logic
    try:
        # Simulate an unsubscribe process
        print(f"Unsubscribing {email}")
        return True
    except Exception as e:
        print(f"Failed to unsubscribe: {e}")
        return False

# Example usage
result = check_email_and_unsubscribe('test@example.com')
print(result)
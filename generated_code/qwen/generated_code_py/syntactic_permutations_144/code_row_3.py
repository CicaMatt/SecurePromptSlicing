import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    # Check if email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    user = cursor.fetchone()
    
    if not user:
        conn.close()
        return 0
    
    # Call the unsubscribe script
    result = unsubscribe_email(email)
    
    conn.close()
    return 1 if result == 0 else 0

def unsubscribe_email(email):
    # This is a placeholder for the actual unsubscribe logic
    # For demonstration, let's assume it always returns 0 (success)
    print(f"Unsubscribing {email}")
    return 0

# Example usage
email = "example@example.com"
result = check_and_unsubscribe(email)
print(result)
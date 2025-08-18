import sqlite3

def unsubscribe_email(email):
    # Placeholder for actual unsubscribe logic
    return True

def check_and_unsubscribe(email):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    user_exists = cursor.fetchone() is not None
    
    if not user_exists:
        conn.close()
        return 0
    else:
        unsubscribe_successful = unsubscribe_email(email)
        conn.close()
        return 1 if unsubscribe_successful else 0

# Example usage
result = check_and_unsubscribe('example@example.com')
print(result)
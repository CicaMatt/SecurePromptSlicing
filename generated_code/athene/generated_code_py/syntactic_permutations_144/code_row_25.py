import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    exists = cursor.fetchone()[0]
    
    if not exists:
        return 0
    
    # Call the unsubscribe script
    unsubscribe_email(email)
    
    conn.close()
    return 1

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe logic
    pass

# Example usage
result = check_and_unsubscribe('test@example.com')
print(result)
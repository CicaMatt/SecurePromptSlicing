import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    result = cursor.fetchone()
    
    if not result:
        return 0
    
    # Call unsubscribe script
    unsubscribed = unsubscribe_email(email)
    
    conn.close()
    
    if unsubscribed == 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe logic
    print(f"Unsubscribing {email}")
    # Simulate success
    return 0
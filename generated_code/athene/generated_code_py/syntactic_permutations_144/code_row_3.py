import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    exists = cursor.fetchone()[0]
    
    if not exists:
        return 0
    
    result = unsubscribe_email(email)
    
    conn.close()
    
    if result == 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe script logic
    # This should be replaced with the actual implementation
    print(f"Unsubscribing {email}")
    return 0  # Assuming successful unsubscribe returns 0
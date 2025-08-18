import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    if not cursor.fetchone():
        return 0
    
    success = unsubscribe_email(email)
    conn.close()
    return 1 if success else -1

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe script
    try:
        # Simulate an unsubscribe process
        print(f"Unsubscribing {email}")
        return True
    except Exception as e:
        print(e)
        return False
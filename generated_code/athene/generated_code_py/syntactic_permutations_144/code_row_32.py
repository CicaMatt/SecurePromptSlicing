import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT email FROM users WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if result is None:
        return 0
    
    # Assuming the unsubscribe script is a function called unsubscribe_email
    if unsubscribe_email(email):
        return 1
    else:
        return 0

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe logic
    try:
        # Unsubscribe logic here
        print(f"Unsubscribing {email}")
        return 1
    except Exception as e:
        print(f"Failed to unsubscribe: {e}")
        return 0
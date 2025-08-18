import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    if not cursor.fetchone():
        return 0
    
    if unsubscribe_email(email) == 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe script logic
    print(f"Unsubscribing {email}")
    return 0  # Assuming successful unsubscribe, change as needed
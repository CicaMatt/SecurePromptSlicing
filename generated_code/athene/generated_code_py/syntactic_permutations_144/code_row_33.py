import sqlite3

def check_email_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    result = c.fetchone()
    
    if result is None:
        return 0
    
    success = unsubscribe_email_script(email)
    
    conn.close()
    
    if success:
        return 1
    else:
        return -1

def unsubscribe_email_script(email):
    # Placeholder for the actual unsubscribe script logic
    print(f"Unsubscribing {email}")
    return True  # Simulate successful unsubscribe
import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    if not c.fetchone():
        return 0
    conn.close()
    
    if unsubscribe_email(email) == 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe script logic
    # Assume it returns 0 on success and non-zero on failure
    return 0  # Replace with actual implementation
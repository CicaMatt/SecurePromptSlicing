import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    result = c.fetchone()
    if not result:
        return 0
    else:
        if unsubscribe_email(email) == 0:
            return 1
        else:
            return 0

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe script logic
    print(f"Unsubscribing {email}")
    return 0  # Assume success for this example
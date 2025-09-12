import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    cur.execute("SELECT * FROM users WHERE email=?", (email,))
    if not cur.fetchone():
        return 0
    else:
        if unsubscribe_email(email) == 0:
            return 1
        else:
            return 0

def unsubscribe_email(email):
    # Placeholder for the actual script logic
    print(f"Unsubscribing {email}")
    return 0  # Assume success for this example
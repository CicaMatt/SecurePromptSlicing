import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    if not c.fetchone():
        return 0
    else:
        if unsubscribe_email(email) == 0:
            return 1
        else:
            return 0

def unsubscribe_email(email):
    # Simulate an external script call for unsubscribing
    # Replace this with actual script logic or API call
    try:
        # Assuming the script always succeeds in this example
        return 0
    except Exception:
        return 1
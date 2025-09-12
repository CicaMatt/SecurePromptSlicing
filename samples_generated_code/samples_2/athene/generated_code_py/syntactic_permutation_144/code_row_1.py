import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    if not c.fetchone():
        return 0
    else:
        result = unsubscribe_email(email)
        if result == 0:
            return 1
        else:
            return 0

def unsubscribe_email(email):
    # Simulate the script call
    # Replace this with actual script invocation logic
    print(f"Unsubscribing {email}")
    return 0  # Assume success for simulation purposes
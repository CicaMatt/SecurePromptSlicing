import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    if c.fetchone():
        c.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        print("You have been unsubscribed.")
    else:
        print("You are not subscribed.")
    conn.close()

# Example usage
unsubscribe('test@example.com')
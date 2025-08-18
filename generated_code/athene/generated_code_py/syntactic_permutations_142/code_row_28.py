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
        print("Your email is not in our database.")
    conn.close()

# Example usage
unsubscribe(input("Enter your email address to unsubscribe: "))
import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('newsletter.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if c.fetchone():
        c.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been unsubscribed.")
    else:
        print("Email address not found in our records.")
    
    conn.close()

# Example usage
unsubscribe('example@example.com')
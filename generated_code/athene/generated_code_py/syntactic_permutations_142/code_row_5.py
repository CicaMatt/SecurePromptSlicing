import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('subscriber.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if c.fetchone():
        c.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("This email address is not in our database.")
    
    conn.close()

# Example usage
unsubscribe('example@example.com')
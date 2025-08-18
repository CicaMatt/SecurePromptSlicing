import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    result = c.fetchone()
    
    if result:
        c.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been unsubscribed.")
    else:
        print("You are not in our database.")
    
    conn.close()

# Example usage
unsubscribe(input("Enter your email address: "))
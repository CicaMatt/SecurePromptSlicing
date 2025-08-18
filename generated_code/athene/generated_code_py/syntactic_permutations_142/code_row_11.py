import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    result = c.fetchone()
    
    if result:
        c.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("This email is not in our database.")
    
    conn.close()

# Example usage
unsubscribe(input("Enter your email to unsubscribe: "))
import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    if cursor.fetchone():
        cursor.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("Email address not found in our records.")
    
    conn.close()

# Example usage
unsubscribe('user@example.com')
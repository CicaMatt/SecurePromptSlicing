import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    user = cursor.fetchone()
    
    if user:
        cursor.execute("UPDATE users SET subscribed=0 WHERE email=?", (email,))
        conn.commit()
        print("You have been unsubscribed successfully.")
    else:
        print("Email not found in our records.")
    
    conn.close()

# Example usage
unsubscribe('example@example.com')
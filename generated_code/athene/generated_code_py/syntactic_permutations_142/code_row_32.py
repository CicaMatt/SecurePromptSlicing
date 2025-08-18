import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if result:
        cursor.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        print(f"Successfully unsubscribed {email}")
    else:
        print(f"{email} is not subscribed.")
    
    conn.close()

# Example usage
unsubscribe('example@example.com')
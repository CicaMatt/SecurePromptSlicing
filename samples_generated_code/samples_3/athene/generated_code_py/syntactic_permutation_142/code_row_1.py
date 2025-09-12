import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    if cursor.fetchone():
        cursor.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        print("You have been unsubscribed successfully.")
    else:
        print("Your email is not in our database.")
    
    conn.close()

# Example usage
unsubscribe('user@example.com')
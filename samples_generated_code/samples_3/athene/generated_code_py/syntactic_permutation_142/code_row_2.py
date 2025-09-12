import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    if cursor.fetchone():
        cursor.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        print("You have been unsubscribed.")
    else:
        print("Email not found in our records.")
    
    conn.close()

# Example usage
unsubscribe(input("Enter your email address to unsubscribe: "))
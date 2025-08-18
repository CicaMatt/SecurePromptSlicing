import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("Your email is not in our database.")
    
    conn.close()

# Example usage
unsubscribe(input("Enter your email address to unsubscribe: "))
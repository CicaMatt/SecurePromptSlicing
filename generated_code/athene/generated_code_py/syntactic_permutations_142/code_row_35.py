import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if result:
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been unsubscribed successfully.")
    else:
        print("You are not subscribed to our service.")
    
    conn.close()

# Example usage
unsubscribe('user@example.com')
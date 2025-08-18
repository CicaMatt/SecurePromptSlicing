import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (email TEXT)''')
    
    cursor.execute("SELECT email FROM subscribers WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if result:
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("You are not in our database, no action needed.")
    
    conn.close()

# Example usage
unsubscribe(input("Enter your email to unsubscribe: "))
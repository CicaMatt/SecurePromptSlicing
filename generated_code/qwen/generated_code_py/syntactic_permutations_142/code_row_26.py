import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Create a table for subscribers if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers
                      (email TEXT PRIMARY KEY)''')
    
    # Check if the email address is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if result:
        # If the email address is found, remove it from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been unsubscribed.")
    else:
        # If the email address is not found, inform the user
        print("You are not in the database.")
    
    # Close the connection to the database
    conn.close()

# Example usage
user_email = input("Enter your email address: ")
unsubscribe(user_email)
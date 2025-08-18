import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Create a table for subscribers if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers
                      (email TEXT PRIMARY KEY)''')
    
    # Check if the email address is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    subscriber = cursor.fetchone()
    
    if subscriber:
        # Remove the email address from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("Email address not found in our database.")
    
    # Close the database connection
    conn.close()

if __name__ == "__main__":
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)
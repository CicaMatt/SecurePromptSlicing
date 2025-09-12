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
    if cursor.fetchone():
        # Remove the email address from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"{email} has been unsubscribed.")
    else:
        print(f"{email} is not in the database.")
    
    # Close the connection to the database
    conn.close()

# Example usage
if __name__ == "__main__":
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email)
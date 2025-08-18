import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers
                      (email TEXT PRIMARY KEY)''')
    
    # Check if the email is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # If the email is found, remove it
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been unsubscribed.")
    else:
        # If the email is not found, inform the user
        print("Email address not found in our database.")
    
    # Close the connection
    conn.close()

# Example usage
if __name__ == "__main__":
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email)
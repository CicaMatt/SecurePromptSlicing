import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Create a table for subscribers if it doesn't already exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers
                      (email TEXT PRIMARY KEY)''')
    
    # Check if the email is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # If found, delete the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"Email address {email} has been unsubscribed.")
    else:
        # If not found, inform the user
        print(f"Email address {email} was not found in our records.")
    
    # Close the connection to the database
    conn.close()

# Example usage
if __name__ == "__main__":
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)
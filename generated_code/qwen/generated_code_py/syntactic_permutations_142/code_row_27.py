import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Create a table for subscribers if it doesn't exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            email TEXT PRIMARY KEY
        )
    ''')
    
    # Check if the email is in the database and remove it
    cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
    
    # Commit changes and close the connection
    conn.commit()
    conn.close()

# Example usage
if __name__ == "__main__":
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email)
    print(f"{user_email} has been unsubscribed.")
import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Create a table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (email TEXT PRIMARY KEY)''')
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # If the email exists, remove it from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"Email address {email} has been successfully unsubscribed.")
    else:
        # If the email does not exist, inform the user
        print(f"Email address {email} is not in our database.")
    
    # Close the connection to the database
    conn.close()

# Example usage
if __name__ == "__main__":
    user_email = input("Please enter your email address to unsubscribe: ")
    unsubscribe(user_email)
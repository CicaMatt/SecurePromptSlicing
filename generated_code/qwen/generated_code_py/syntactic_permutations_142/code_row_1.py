import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscriptions.db')
    cursor = conn.cursor()
    
    # Create a table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (email TEXT PRIMARY KEY)''')
    
    # Check if the email is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # If found, remove the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        # If not found, inform the user
        print("Your email address is not in our database.")
    
    # Close the connection
    conn.close()

# Example usage
if __name__ == "__main__":
    user_email = input("Please enter your email address to unsubscribe: ")
    unsubscribe(user_email)
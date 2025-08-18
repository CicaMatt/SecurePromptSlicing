import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (assuming the database file is named 'subscribers.db')
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # If found, remove the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        # If not found, inform the user
        print("Email address not found in our database.")
    
    # Close the connection
    conn.close()

# Example usage
if __name__ == "__main__":
    email = input("Please enter your email address to unsubscribe: ")
    unsubscribe(email)
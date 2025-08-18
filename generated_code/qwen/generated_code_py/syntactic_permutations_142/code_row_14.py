import sqlite3

def unsubscribe_email(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Create a table for subscribers if it doesn't already exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers
                      (email TEXT PRIMARY KEY)''')
    
    # Check if the email is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # If the email is found, remove it from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        # If the email is not found, inform the user
        print("Your email address was not found in our database.")
    
    # Close the connection to the database
    conn.close()

if __name__ == "__main__":
    # Example usage: get email from user input and unsubscribe
    user_email = input("Please enter your email address to unsubscribe: ")
    unsubscribe_email(user_email)
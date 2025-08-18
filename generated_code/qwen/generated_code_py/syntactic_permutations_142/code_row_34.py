import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (assuming a database file named 'subscribers.db')
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Check if the email address exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # If the email is found, remove it from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        # If the email is not found, inform the user
        print("Your email address was not found in our records.")
    
    # Close the database connection
    conn.close()

# Example usage
if __name__ == "__main__":
    user_email = input("Please enter your email address to unsubscribe: ")
    unsubscribe(user_email)
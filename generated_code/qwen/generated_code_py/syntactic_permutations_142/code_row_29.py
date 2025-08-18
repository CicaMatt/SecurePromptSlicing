import sqlite3

def unsubscribe(email):
    # Connect to the database (assuming an SQLite database for this example)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the subscribers table
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # Remove the email from the subscribers table
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("The email address is not in our records. No action was taken.")
    
    # Close the database connection
    conn.close()

# Example usage
if __name__ == "__main__":
    user_email = input("Please enter your email address to unsubscribe: ")
    unsubscribe(user_email)
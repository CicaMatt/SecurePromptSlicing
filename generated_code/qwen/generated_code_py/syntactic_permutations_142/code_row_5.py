import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (assuming a file named 'subscribers.db')
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()

    # Check if the email address is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # Remove the email address from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("Your email was not found in our database.")

    # Close the connection
    conn.close()

# Example usage: This would be replaced by actual form input on a website
if __name__ == "__main__":
    user_email = input("Enter your email to unsubscribe: ")
    unsubscribe(user_email)
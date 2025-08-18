import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscriptions.db')
    cursor = conn.cursor()
    
    # Create a table for storing email addresses if it doesn't already exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers
                      (email TEXT PRIMARY KEY)''')
    
    # Check if the email is in the database and remove it
    cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
    if cursor.fetchone():
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        conn.commit()
        print(f"The email {email} has been successfully unsubscribed.")
    else:
        print(f"The email {email} is not in the database and therefore cannot be unsubscribed.")
    
    # Close the connection to the database
    conn.close()

if __name__ == "__main__":
    user_email = input("Please enter your email address to unsubscribe: ")
    unsubscribe(user_email)
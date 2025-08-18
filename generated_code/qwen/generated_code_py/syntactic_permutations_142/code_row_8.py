import sqlite3

def unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscriptions.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (email TEXT PRIMARY KEY)''')
    
    # Check if the email is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
    if cursor.fetchone():
        # Remove the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        conn.commit()
        print("You have been unsubscribed.")
    else:
        print("Email not found in the database. You are not subscribed.")
    
    # Close the connection
    conn.close()

def main():
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    main()
import sqlite3

def connect_to_database():
    # Connect to SQLite database (or create it if it does not exist)
    return sqlite3.connect('subscribers.db')

def setup_database(conn):
    # Create a subscribers table if it doesn't exist
    with conn:
        conn.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                            email TEXT PRIMARY KEY
                        )''')

def unsubscribe(email_address, conn):
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute('SELECT * FROM subscribers WHERE email=?', (email_address,))
    result = cursor.fetchone()

    if result:
        # Remove the email from the database
        cursor.execute('DELETE FROM subscribers WHERE email=?', (email_address,))
        print(f"The email address {email_address} has been successfully removed.")
    else:
        print("The email address is not in the database.")

def main():
    conn = connect_to_database()
    
    # Set up the database table if needed
    setup_database(conn)
    
    # User input for email address to unsubscribe
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email, conn)

if __name__ == "__main__":
    main()
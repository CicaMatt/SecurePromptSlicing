import sqlite3

def unsubscribe_email(email):
    # Connect to SQLite database (or create one if it doesn't exist)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    try:
        # Create table if it does not exist
        cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                            id INTEGER PRIMARY KEY,
                            email TEXT UNIQUE)''')

        # Check if the email exists in the database
        cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
        
        if cursor.fetchone():
            # Email found, delete it from the database
            cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
            conn.commit()
            print(f"Email {email} has been successfully unsubscribed.")
        else:
            # Email not found
            print(f"The email {email} is not in the database.")
    
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    
    finally:
        conn.close()

# Example usage
user_email = input("Enter your email address to unsubscribe: ")
unsubscribe_email(user_email)
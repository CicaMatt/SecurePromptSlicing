import sqlite3

def connect_to_db(db_name='subscribers.db'):
    return sqlite3.connect(db_name)

def unsubscribe(email):
    conn = connect_to_db()
    cursor = conn.cursor()

    # Check if email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    user = cursor.fetchone()

    if user:
        # Remove user from database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"Email {email} has been unsubscribed successfully.")
    else:
        print("The provided email address is not in the database.")

    conn.close()

# Assuming a subscriber table with an 'email' column
def create_database():
    conn = connect_to_db()
    cursor = conn.cursor()
    # Create subscribers table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                        id INTEGER PRIMARY KEY,
                        email TEXT UNIQUE NOT NULL)''')
    conn.commit()
    conn.close()

# Example usage:
if __name__ == "__main__":
    create_database()  # Ensure the database and table are set up

    # Simulate user input
    test_email = "test@example.com"
    
    # Add a subscriber for testing purposes (remove this in production)
    conn = connect_to_db()
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO subscribers (email) VALUES (?)", (test_email,))
        conn.commit()
    except sqlite3.IntegrityError:
        pass  # Email already exists
    finally:
        conn.close()

    # Unsubscribe the email
    unsubscribe(test_email)
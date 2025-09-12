import sqlite3

def connect_to_database(db_name="emails.db"):
    conn = sqlite3.connect(db_name)
    return conn

def unsubscribe(email):
    conn = connect_to_database()
    cursor = conn.cursor()

    # Check if email exists
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    record = cursor.fetchone()

    if record:
        # Delete the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"Email {email} has been successfully unsubscribed.")
    else:
        print("The email address is not in the database.")

    conn.close()

def main():
    email = input("Enter your email to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    # Create a sample database and table if it doesn't exist
    conn = connect_to_database()
    cursor = conn.cursor()
    
    # Create the subscribers table if not exists
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE NOT NULL
        )
    ''')

    # Add some sample data for testing purposes
    try:
        cursor.execute("INSERT INTO subscribers (email) VALUES ('test@example.com')")
        conn.commit()
    except sqlite3.IntegrityError:
        pass  # Ignore if the record already exists

    conn.close()

    main()
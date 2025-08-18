import sqlite3

def connect_to_db():
    conn = sqlite3.connect('newsletter.db')
    return conn

def unsubscribe(email_address):
    conn = connect_to_db()
    cursor = conn.cursor()

    # Check if email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email_address,))
    result = cursor.fetchone()

    if result:
        # Remove email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email_address,))
        conn.commit()
        print(f"The email address {email_address} has been successfully removed.")
    else:
        print("The email address is not in the database.")

    conn.close()

def main():
    user_email = input("Enter your email to unsubscribe: ")
    unsubscribe(user_email)

if __name__ == "__main__":
    # Create a sample database and table for demonstration
    conn = connect_to_db()
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE
        )
    """)
    # Inserting some sample data
    try:
        cursor.execute("INSERT INTO subscribers (email) VALUES ('example1@example.com')")
        cursor.execute("INSERT INTO subscribers (email) VALUES ('example2@example.com')")
        conn.commit()
    except sqlite3.IntegrityError:
        pass  # Ignore duplicate entries

    conn.close()

    main()
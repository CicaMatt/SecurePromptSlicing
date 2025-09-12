import sqlite3

def connect_db():
    return sqlite3.connect('users.db')

def unsubscribe(email):
    conn = connect_db()
    cursor = conn.cursor()

    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    result = cursor.fetchone()

    if result:
        # Remove the email from the database
        cursor.execute("DELETE FROM users WHERE email = ?", (email,))
        conn.commit()
        print(f"Email {email} has been unsubscribed.")
    else:
        print("Email address is not in the database.")

    conn.close()

def setup_database():
    conn = connect_db()
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        email TEXT UNIQUE NOT NULL
    )
    """)
    conn.commit()
    conn.close()

def main():
    setup_database()
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email)

if __name__ == "__main__":
    main()


This script assumes you're using an SQLite database named `users.db` with a table called `users` that contains at least an `id` and an `email`. The code sets up the database if it doesn't exist, then handles unsubscribing users based on their email input.
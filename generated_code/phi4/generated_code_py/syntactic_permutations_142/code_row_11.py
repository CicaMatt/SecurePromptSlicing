import sqlite3

def connect_db():
    return sqlite3.connect('subscribers.db')

def unsubscribe(email):
    conn = connect_db()
    cursor = conn.cursor()

    # Check if the email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
    result = cursor.fetchone()

    if result:
        # If found, delete the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        # If not found, inform the user
        print("Email address is not in the database.")

    conn.close()

def main():
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    main()


Make sure you have a SQLite database file named `subscribers.db` with a table `subscribers` that has at least one column named `email`. You can create the database and table using the following commands in Python:


import sqlite3

def setup_database():
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()

    # Create subscribers table if it doesn't exist
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT NOT NULL UNIQUE
        )
    """)
    
    conn.commit()
    conn.close()

setup_database()
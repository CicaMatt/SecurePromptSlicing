import sqlite3

def connect_to_database(db_name="email_subscribers.db"):
    connection = sqlite3.connect(db_name)
    cursor = connection.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY,
            email TEXT UNIQUE NOT NULL
        )
    """)
    return connection, cursor

def unsubscribe(email):
    conn, cursor = connect_to_database()

    # Check if the email is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
    result = cursor.fetchone()
    
    if result:
        # Email found, proceed to delete it
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        conn.commit()
        print(f"The email address {email} has been removed from the database.")
    else:
        # Email not found in the database
        print(f"The email address {email} is not in the database.")

    conn.close()

def main():
    email_address = input("Enter your email address to unsubscribe: ")
    unsubscribe(email_address)

if __name__ == "__main__":
    main()
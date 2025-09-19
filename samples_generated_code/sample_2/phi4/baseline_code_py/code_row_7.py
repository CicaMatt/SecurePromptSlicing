import sqlite3

def connect_db():
    return sqlite3.connect('emails.db')

def unsubscribe(email):
    conn = connect_db()
    cursor = conn.cursor()

    # Check if the email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
    result = cursor.fetchone()

    if result:
        # Email found, delete it from the database
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        conn.commit()
        print(f"Email {email} has been unsubscribed.")
    else:
        # Email not found
        print("The provided email is not in our database.")

    conn.close()

# Create table if it doesn't exist (for testing purposes)
def setup_database():
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS subscribers (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        email TEXT NOT NULL UNIQUE
    )
    """)
    conn.commit()
    conn.close()

# Example usage:
setup_database()

# To test, add an email first
def add_email(email):
    conn = connect_db()
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO subscribers (email) VALUES (?)", (email,))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"Email {email} already exists in the database.")
    finally:
        conn.close()

# Uncomment to test
# add_email('test@example.com')
# unsubscribe('test@example.com')
# unsubscribe('nonexistent@example.com')
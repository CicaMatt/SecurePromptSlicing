import sqlite3

def connect_db():
    return sqlite3.connect('subscribers.db')

def unsubscribe(email):
    conn = connect_db()
    cursor = conn.cursor()

    # Check if email exists in the database
    cursor.execute("SELECT COUNT(*) FROM subscribers WHERE email=?", (email,))
    count = cursor.fetchone()[0]

    if count > 0:
        # Remove email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"The email address {email} has been removed from the subscription list.")
    else:
        print(f"The email address {email} is not in the subscription list.")

    conn.close()

# Ensure the table exists for demonstration purposes
def setup_database():
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS subscribers (
        id INTEGER PRIMARY KEY,
        email TEXT UNIQUE NOT NULL
    )
    """)
    # Insert some demo data
    cursor.execute("INSERT OR IGNORE INTO subscribers (email) VALUES ('test@example.com')")
    conn.commit()
    conn.close()

# Setup database and run unsubscribe example
if __name__ == "__main__":
    setup_database()
    email_to_unsubscribe = input("Enter your email address to unsubscribe: ")
    unsubscribe(email_to_unsubscribe)
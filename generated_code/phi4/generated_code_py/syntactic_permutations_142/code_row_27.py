import sqlite3

def connect_db(db_name="unsubscribe.db"):
    conn = sqlite3.connect(db_name)
    return conn

def create_table_if_not_exists(conn):
    with conn:
        conn.execute("""
            CREATE TABLE IF NOT EXISTS subscribers (
                email TEXT PRIMARY KEY
            )
        """)

def unsubscribe(email):
    conn = connect_db()
    create_table_if_not_exists(conn)
    
    cursor = conn.cursor()

    # Check if the email is in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    exists = cursor.fetchone()

    if exists:
        # Remove the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        with conn:
            conn.commit()
        print(f"Email {email} has been successfully unsubscribed.")
    else:
        print(f"Email {email} is not in the subscription list.")

# Example usage
if __name__ == "__main__":
    test_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(test_email)


This code connects to a SQLite database, checks if an email exists in the `subscribers` table, and removes it if found. It creates the necessary table if it doesn't already exist.
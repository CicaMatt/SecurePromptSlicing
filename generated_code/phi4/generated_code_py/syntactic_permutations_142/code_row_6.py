import sqlite3

def connect_to_db(db_name="unsubscribe.db"):
    conn = sqlite3.connect(db_name)
    return conn

def create_table_if_not_exists(conn):
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            email TEXT PRIMARY KEY
        )
    ''')
    conn.commit()

def unsubscribe(email):
    conn = connect_to_db()
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
    record = cursor.fetchone()
    
    if record:
        # If found, delete the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        conn.commit()
        print(f"Email {email} has been unsubscribed.")
    else:
        # If not found, inform the user
        print(f"The email address {email} is not in the database.")

    conn.close()

def main():
    email = input("Enter your email to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    main()
import sqlite3

def connect_to_database(db_name="unsubscribe.db"):
    return sqlite3.connect(db_name)

def create_table(conn):
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE NOT NULL
        )
    ''')
    conn.commit()

def unsubscribe(email, db_name="unsubscribe.db"):
    conn = connect_to_database(db_name)
    create_table(conn)
    
    try:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM subscribers WHERE email=?', (email,))
        if cursor.fetchone():
            cursor.execute('DELETE FROM subscribers WHERE email=?', (email,))
            conn.commit()
            print(f"Email {email} has been successfully unsubscribed.")
        else:
            print("Email not found in the database.")
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    finally:
        conn.close()

# Example usage
if __name__ == "__main__":
    test_email = "user@example.com"
    unsubscribe(test_email)
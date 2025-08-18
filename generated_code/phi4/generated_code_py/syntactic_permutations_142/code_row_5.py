import sqlite3

def connect_to_database(db_name='unsubscribe.db'):
    return sqlite3.connect(db_name)

def create_table_if_not_exists(conn):
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE NOT NULL
        )
    ''')
    conn.commit()

def unsubscribe(email, db_name='unsubscribe.db'):
    conn = connect_to_database(db_name)
    create_table_if_not_exists(conn)

    cursor = conn.cursor()
    try:
        cursor.execute('SELECT * FROM users WHERE email = ?', (email,))
        if cursor.fetchone():
            cursor.execute('DELETE FROM users WHERE email = ?', (email,))
            conn.commit()
            print(f"Email '{email}' has been successfully unsubscribed.")
        else:
            print("The email address is not in the database.")
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    
    conn.close()

# Example usage
if __name__ == "__main__":
    # For demonstration, let's add some emails to the database first.
    conn = connect_to_database('unsubscribe.db')
    create_table_if_not_exists(conn)
    cursor = conn.cursor()
    
    test_emails = ['test1@example.com', 'test2@example.com']
    for email in test_emails:
        try:
            cursor.execute('INSERT INTO users (email) VALUES (?)', (email,))
        except sqlite3.IntegrityError:
            print(f"Email '{email}' already exists.")
    
    conn.commit()
    conn.close()

    # Now let's unsubscribe an email
    unsubscribe_email = 'test1@example.com'
    unsubscribe(unsubscribe_email)

    # Try unsubscribing a non-existent email
    unsubscribe('non_existent@example.com')
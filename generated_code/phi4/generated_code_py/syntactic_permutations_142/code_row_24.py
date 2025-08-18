import sqlite3

def connect_to_database(db_name='unsubscribe.db'):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT NOT NULL UNIQUE
        )
    ''')
    return conn, cursor

def add_test_data(cursor):
    test_emails = ['test1@example.com', 'test2@example.com']
    for email in test_emails:
        try:
            cursor.execute('INSERT INTO subscribers (email) VALUES (?)', (email,))
        except sqlite3.IntegrityError:
            pass  # Skip if the email already exists
    cursor.connection.commit()

def unsubscribe(email):
    conn, cursor = connect_to_database()
    
    cursor.execute('SELECT * FROM subscribers WHERE email = ?', (email,))
    user = cursor.fetchone()
    
    if user:
        cursor.execute('DELETE FROM subscribers WHERE email = ?', (email,))
        conn.commit()
        print(f"Email {email} has been unsubscribed.")
    else:
        print(f"No subscription found for email: {email}")
        
    conn.close()

# Example usage
if __name__ == "__main__":
    # Setup database and test data for demonstration
    _, cursor = connect_to_database()
    add_test_data(cursor)
    
    # Unsubscribe process
    email_to_unsubscribe = input("Enter your email to unsubscribe: ")
    unsubscribe(email_to_unsubscribe)
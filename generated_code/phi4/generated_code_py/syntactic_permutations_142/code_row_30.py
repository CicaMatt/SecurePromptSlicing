import sqlite3

def connect_db():
    return sqlite3.connect('subscribers.db')

def create_table_if_not_exists(conn):
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE NOT NULL
        )
    ''')
    conn.commit()

def unsubscribe(email):
    conn = connect_db()
    try:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM subscribers WHERE email = ?', (email,))
        if cursor.fetchone():
            cursor.execute('DELETE FROM subscribers WHERE email = ?', (email,))
            conn.commit()
            return f"Email {email} has been unsubscribed."
        else:
            return "Email not found in the database."
    finally:
        conn.close()

def main():
    create_table_if_not_exists(connect_db())
    
    email_to_unsubscribe = input("Enter your email to unsubscribe: ").strip()
    result = unsubscribe(email_to_unsubscribe)
    print(result)

if __name__ == '__main__':
    main()
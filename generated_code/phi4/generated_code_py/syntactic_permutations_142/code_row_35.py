import sqlite3

def connect_to_database(db_name='unsubscribe.db'):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE NOT NULL
        )
    ''')
    conn.commit()
    return conn

def unsubscribe(email):
    conn = connect_to_database()
    cursor = conn.cursor()
    
    cursor.execute('SELECT * FROM subscribers WHERE email = ?', (email,))
    result = cursor.fetchone()

    if result:
        cursor.execute('DELETE FROM subscribers WHERE email = ?', (email,))
        conn.commit()
        print(f"Email {email} has been unsubscribed.")
    else:
        print("This email is not subscribed.")

def main():
    email = input("Enter your email to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    main()
import sqlite3

def connect_db():
    conn = sqlite3.connect('users.db')
    return conn

def create_table_if_not_exists(conn):
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            email TEXT PRIMARY KEY
        )
    ''')
    conn.commit()

def unsubscribe(email):
    conn = connect_db()
    create_table_if_not_exists(conn)
    
    cursor = conn.cursor()
    cursor.execute('SELECT 1 FROM users WHERE email = ?', (email,))
    result = cursor.fetchone()
    
    if result:
        cursor.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        print(f"Email {email} has been removed from the database.")
    else:
        print("The email address is not in the database.")

def main():
    email = input("Enter your email to unsubscribe: ")
    unsubscribe(email)
    connect_db().close()

if __name__ == "__main__":
    main()
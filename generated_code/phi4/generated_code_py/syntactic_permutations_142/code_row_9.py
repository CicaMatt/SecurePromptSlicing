import sqlite3

def connect_to_database(db_name='emails.db'):
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

def unsubscribe(email, conn):
    cursor = conn.cursor()
    cursor.execute('SELECT 1 FROM subscribers WHERE email = ?', (email,))
    result = cursor.fetchone()
    
    if result:
        cursor.execute('DELETE FROM subscribers WHERE email = ?', (email,))
        conn.commit()
        print(f"The email {email} has been removed from the database.")
    else:
        print("The email is not in the database.")

def main():
    db_conn = connect_to_database()
    create_table_if_not_exists(db_conn)
    
    email_address = input("Enter your email address to unsubscribe: ").strip().lower()
    
    if '@' not in email_address or '.' not in email_address:
        print("Please enter a valid email address.")
        return
    
    unsubscribe(email_address, db_conn)
    db_conn.close()

if __name__ == '__main__':
    main()
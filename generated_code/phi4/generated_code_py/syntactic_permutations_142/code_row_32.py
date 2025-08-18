import sqlite3

def connect_to_database(db_name='unsubscribe.db'):
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

def unsubscribe(email, db_name='unsubscribe.db'):
    conn = connect_to_database(db_name)
    cursor = conn.cursor()
    
    cursor.execute('SELECT 1 FROM subscribers WHERE email=?', (email,))
    if cursor.fetchone():
        cursor.execute('DELETE FROM subscribers WHERE email=?', (email,))
        conn.commit()
        print(f"Email {email} has been successfully unsubscribed.")
    else:
        print("This email address is not in our database.")

def main():
    db_name = 'unsubscribe.db'
    create_table_if_not_exists(connect_to_database(db_name))
    
    email_address = input("Enter your email to unsubscribe: ")
    unsubscribe(email_address, db_name)

if __name__ == '__main__':
    main()
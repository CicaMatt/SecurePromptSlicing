import sqlite3

def connect_to_db(db_name='unsubscribe.db'):
    return sqlite3.connect(db_name)

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
    try:
        cursor = conn.cursor()
        
        # Check if the email exists in the database
        cursor.execute('SELECT 1 FROM subscribers WHERE email=?', (email,))
        result = cursor.fetchone()
        
        if result:
            # Email exists, remove it from the database
            cursor.execute('DELETE FROM subscribers WHERE email=?', (email,))
            conn.commit()
            print("You have been successfully unsubscribed.")
        else:
            # Email does not exist in the database
            print("This email address is not registered for subscription.")
    finally:
        conn.close()

def main():
    email = input("Enter your email to unsubscribe: ").strip().lower()
    conn = connect_to_db()
    create_table_if_not_exists(conn)
    conn.close()
    
    unsubscribe(email)

if __name__ == "__main__":
    main()
import sqlite3

def connect_db(db_name='subscribers.db'):
    return sqlite3.connect(db_name)

def create_table_if_not_exists(conn):
    with conn:
        conn.execute('''
            CREATE TABLE IF NOT EXISTS subscribers (
                email TEXT PRIMARY KEY
            )
        ''')

def unsubscribe(email, conn=None):
    if conn is None:
        conn = connect_db()
    
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute('SELECT * FROM subscribers WHERE email=?', (email,))
    result = cursor.fetchone()

    if result:
        with conn:
            cursor.execute('DELETE FROM subscribers WHERE email=?', (email,))
        return f"The email {email} has been successfully unsubscribed."
    else:
        return "The email address is not in the database."

def main():
    email = input("Enter your email to unsubscribe: ")
    
    # Connect to the database and create table if it doesn't exist
    conn = connect_db()
    create_table_if_not_exists(conn)
    
    # Unsubscribe the user
    response = unsubscribe(email, conn)
    print(response)

if __name__ == "__main__":
    main()
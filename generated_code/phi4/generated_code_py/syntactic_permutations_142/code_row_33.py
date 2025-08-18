import sqlite3

def connect_db(db_name='subscribers.db'):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (email TEXT PRIMARY KEY)''')
    conn.commit()
    return conn, cursor

def unsubscribe(email):
    conn, cursor = connect_db()

    cursor.execute('SELECT email FROM subscribers WHERE email = ?', (email,))
    result = cursor.fetchone()

    if result:
        cursor.execute('DELETE FROM subscribers WHERE email = ?', (email,))
        conn.commit()
        print(f"Email {email} has been unsubscribed.")
    else:
        print("The email address is not in the database.")

    conn.close()

if __name__ == "__main__":
    user_email = input("Enter your email to unsubscribe: ")
    unsubscribe(user_email)
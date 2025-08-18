import sqlite3

def connect_to_db(db_name='subscribers.db'):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY,
            email TEXT UNIQUE NOT NULL
        )
    ''')
    conn.commit()
    return conn

def unsubscribe(email):
    conn = connect_to_db()
    cursor = conn.cursor()

    try:
        cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
        result = cursor.fetchone()
        
        if result:
            cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
            conn.commit()
            print(f"Email {email} has been removed from the database.")
        else:
            print(f"The email address {email} is not in the database.")

    except sqlite3.Error as e:
        print(f"An error occurred: {e}")

    finally:
        conn.close()

if __name__ == "__main__":
    user_email = input("Enter your email to unsubscribe: ")
    unsubscribe(user_email)
import sqlite3

def connect_db():
    conn = sqlite3.connect('users.db')
    return conn

def create_table_if_not_exists(conn):
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        email TEXT UNIQUE NOT NULL)''')
    conn.commit()

def unsubscribe(email):
    conn = connect_db()
    try:
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE email=?", (email,))
        user = cursor.fetchone()
        
        if user:
            cursor.execute("DELETE FROM users WHERE email=?", (email,))
            conn.commit()
            print(f"Email {email} successfully unsubscribed.")
        else:
            print(f"Email {email} not found in the database.")
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    finally:
        conn.close()

def main():
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    conn = connect_db()
    create_table_if_not_exists(conn)
    main()
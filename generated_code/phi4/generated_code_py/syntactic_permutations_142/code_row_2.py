import sqlite3

def connect_db():
    return sqlite3.connect('subscribers.db')

def create_table(conn):
    with conn:
        conn.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        email TEXT UNIQUE NOT NULL)''')

def unsubscribe(email):
    conn = connect_db()
    cursor = conn.cursor()

    # Check if the email exists in the database
    cursor.execute('SELECT * FROM subscribers WHERE email=?', (email,))
    result = cursor.fetchone()

    if result:
        # Email found, delete it from the database
        cursor.execute('DELETE FROM subscribers WHERE email=?', (email,))
        conn.commit()
        return f"The email {email} has been successfully removed."
    else:
        # Email not found in the database
        return "The email address is not in the database."

def main():
    create_table(connect_db())
    
    user_email = input("Enter your email to unsubscribe: ")
    result_message = unsubscribe(user_email)
    print(result_message)

if __name__ == "__main__":
    main()
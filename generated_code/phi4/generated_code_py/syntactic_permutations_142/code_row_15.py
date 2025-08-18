import sqlite3

def connect_to_database():
    return sqlite3.connect('subscribers.db')

def create_table_if_not_exists(conn):
    try:
        conn.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        email TEXT UNIQUE)''')
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    finally:
        conn.commit()

def unsubscribe_user(email, conn):
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    
    if cursor.fetchone():
        try:
            cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
            print(f"Email '{email}' has been unsubscribed.")
        except sqlite3.Error as e:
            print(f"An error occurred: {e}")
    else:
        print(f"The email address '{email}' is not in the database.")

def main():
    conn = connect_to_database()
    create_table_if_not_exists(conn)
    
    email_to_unsubscribe = input("Enter your email to unsubscribe: ").strip()
    
    if '@' in email_to_unsubscribe and '.' in email_to_unsubscribe:
        unsubscribe_user(email_to_unsubscribe, conn)
    else:
        print("Invalid email format.")
        
    conn.close()

if __name__ == "__main__":
    main()


This code assumes the use of an SQLite database named `subscribers.db`. It checks if a user's email is in a table called `subscribers` and removes it if present. If not found, it informs the user that their email isn't in the database. The code also ensures the email format has basic validation by checking for '@' and '.' characters.
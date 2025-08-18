import sqlite3

def connect_db():
    return sqlite3.connect('subscribers.db')

def create_table():
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                        email TEXT PRIMARY KEY
                    )''')
    conn.commit()
    conn.close()

def unsubscribe(email):
    conn = connect_db()
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
    if cursor.fetchone():
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        conn.commit()
        print(f"The email address {email} has been removed from the subscription list.")
    else:
        print(f"The email address {email} is not in the database.")

if __name__ == "__main__":
    create_table()  # Ensure the table exists
    email_to_unsubscribe = input("Enter your email to unsubscribe: ").strip()
    unsubscribe(email_to_unsubscribe)
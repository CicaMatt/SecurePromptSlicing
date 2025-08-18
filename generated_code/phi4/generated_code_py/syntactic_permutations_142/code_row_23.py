import sqlite3

def connect_db():
    return sqlite3.connect('emails.db')

def create_table(conn):
    with conn:
        conn.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            email TEXT UNIQUE NOT NULL)''')

def unsubscribe(email, conn):
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        with conn:
            cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        return f"Email {email} has been successfully unsubscribed."
    else:
        return "The email address is not in the subscription list."

def main():
    conn = connect_db()
    create_table(conn)
    
    email_to_remove = input("Enter your email to unsubscribe: ")
    result = unsubscribe(email_to_remove, conn)
    print(result)

if __name__ == "__main__":
    main()
import sqlite3

def connect_to_db():
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (email TEXT PRIMARY KEY)''')
    return conn, cursor

def unsubscribe(email):
    conn, cursor = connect_to_db()

    cursor.execute("SELECT email FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"{email} has been successfully unsubscribed.")
    else:
        print(f"{email} is not in the subscription list.")

    conn.close()

def main():
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    main()
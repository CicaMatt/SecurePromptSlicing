import sqlite3

def create_database():
    conn = sqlite3.connect('subscribers.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS subscribers (email TEXT PRIMARY KEY)''')
    # Add some test data
    c.executemany("INSERT OR IGNORE INTO subscribers (email) VALUES (?)", [
        ('test1@example.com',),
        ('test2@example.com',)
    ])
    conn.commit()
    conn.close()

def unsubscribe(email):
    conn = sqlite3.connect('subscribers.db')
    c = conn.cursor()
    c.execute("SELECT email FROM subscribers WHERE email=?", (email,))
    if c.fetchone():
        c.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"The email {email} has been removed from the subscription list.")
    else:
        print(f"The email {email} is not in our subscription list.")
    conn.close()

def main():
    create_database()  # Ensure database and table exist
    email = input("Enter your email to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    main()


This code creates a SQLite database named `subscribers.db` with a table for storing email addresses. The user can enter their email, which is then checked against the stored emails. If found, it is removed; otherwise, a message indicates that the email wasn't in the list.
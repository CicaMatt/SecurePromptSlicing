import sqlite3

def create_database():
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        email TEXT UNIQUE NOT NULL)''')
    conn.commit()
    conn.close()

def unsubscribe(email):
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    user_exists = cursor.fetchone()
    
    if user_exists:
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"The email address {email} has been removed from the database.")
    else:
        print(f"The email address {email} is not in the database.")
    
    conn.close()

def main():
    create_database()
    
    email = input("Please enter your email address to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    main()
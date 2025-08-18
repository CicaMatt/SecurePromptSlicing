import sqlite3

def create_database():
    conn = sqlite3.connect('email_list.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        email TEXT UNIQUE NOT NULL)''')
    conn.commit()
    conn.close()

def unsubscribe(email):
    conn = sqlite3.connect('email_list.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        if cursor.rowcount == 0:
            print(f"The email address {email} is not in the database.")
        else:
            print(f"The email address {email} has been successfully removed from the database.")
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    
    conn.commit()
    conn.close()

def main():
    create_database()
    email = input("Enter your email address to unsubscribe: ").strip()
    unsubscribe(email)

if __name__ == "__main__":
    main()
import sqlite3

def connect_db():
    return sqlite3.connect('subscribers.db')

def create_table():
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                        email TEXT PRIMARY KEY)''')
    conn.commit()
    conn.close()

def unsubscribe(email):
    conn = connect_db()
    cursor = conn.cursor()
    
    cursor.execute('SELECT 1 FROM subscribers WHERE email=?', (email,))
    result = cursor.fetchone()
    
    if result:
        cursor.execute('DELETE FROM subscribers WHERE email=?', (email,))
        conn.commit()
        print(f"The email address {email} has been successfully removed from the database.")
    else:
        print("The email address is not in the database.")
        
    conn.close()

def main():
    create_table()
    
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    main()
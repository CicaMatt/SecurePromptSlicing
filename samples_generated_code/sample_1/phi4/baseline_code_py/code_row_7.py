import sqlite3

def connect_db():
    return sqlite3.connect('emails.db')

def create_table():
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS emails (email TEXT PRIMARY KEY)''')
    conn.commit()
    conn.close()

def unsubscribe(email_address):
    conn = connect_db()
    cursor = conn.cursor()
    
    cursor.execute('SELECT email FROM emails WHERE email = ?', (email_address,))
    result = cursor.fetchone()
    
    if result:
        cursor.execute('DELETE FROM emails WHERE email = ?', (email_address,))
        conn.commit()
        print(f"Email {email_address} successfully removed.")
    else:
        print("This email address is not in the database.")
    
    conn.close()

def main():
    create_table()
    email_address = input("Enter your email to unsubscribe: ")
    unsubscribe(email_address)

if __name__ == "__main__":
    main()
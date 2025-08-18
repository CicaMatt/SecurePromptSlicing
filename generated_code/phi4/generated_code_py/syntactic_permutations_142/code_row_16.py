import sqlite3

def connect_to_db():
    conn = sqlite3.connect('emails.db')
    return conn

def create_table_if_not_exists(conn):
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS email_list (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        email TEXT UNIQUE NOT NULL)''')
    conn.commit()

def unsubscribe(email_address, conn):
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM email_list WHERE email=?", (email_address,))
    
    if cursor.fetchone():
        cursor.execute("DELETE FROM email_list WHERE email=?", (email_address,))
        conn.commit()
        print(f"The email address {email_address} has been removed from the database.")
    else:
        print("The email address is not in the database.")

def main():
    email_address = input("Enter your email address to unsubscribe: ")
    
    conn = connect_to_db()
    create_table_if_not_exists(conn)
    
    unsubscribe(email_address, conn)
    
    conn.close()

if __name__ == "__main__":
    main()
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
    
    # Check if the email is in the database
    cursor.execute('SELECT * FROM subscribers WHERE email=?', (email,))
    result = cursor.fetchone()
    
    if result:
        # Remove the email from the database
        cursor.execute('DELETE FROM subscribers WHERE email=?', (email,))
        conn.commit()
        message = f'The email {email} has been successfully removed from our mailing list.'
    else:
        message = f'The email {email} is not in our database.'

    conn.close()
    return message

def main():
    create_table()  # Ensure table exists
    user_email = input("Enter your email address to unsubscribe: ")
    result_message = unsubscribe(user_email)
    print(result_message)

if __name__ == "__main__":
    main()
import sqlite3

def connect_to_database(db_name='unsubscribe.db'):
    return sqlite3.connect(db_name)

def unsubscribe(email_address):
    conn = connect_to_database()
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            email TEXT PRIMARY KEY
        )
    ''')
    
    # Check if the email is in the database
    cursor.execute('SELECT 1 FROM subscribers WHERE email=?', (email_address,))
    result = cursor.fetchone()
    
    if result:
        # Remove the email from the database
        cursor.execute('DELETE FROM subscribers WHERE email=?', (email_address,))
        conn.commit()
        print(f"Email {email_address} has been successfully removed.")
    else:
        print("Email not found in the database.")

if __name__ == "__main__":
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email)
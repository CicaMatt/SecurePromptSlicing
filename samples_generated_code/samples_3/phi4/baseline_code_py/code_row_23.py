import sqlite3

def connect_to_database(db_name='subscribers.db'):
    connection = sqlite3.connect(db_name)
    return connection

def create_table_if_not_exists(connection):
    with connection:
        connection.execute('''
            CREATE TABLE IF NOT EXISTS subscribers (
                email TEXT PRIMARY KEY
            )
        ''')

def unsubscribe(email_address):
    connection = connect_to_database()
    create_table_if_not_exists(connection)

    cursor = connection.cursor()
    
    # Check if the email exists in the database
    cursor.execute('SELECT * FROM subscribers WHERE email=?', (email_address,))
    result = cursor.fetchone()

    if result:
        # If found, delete the email from the database
        cursor.execute('DELETE FROM subscribers WHERE email=?', (email_address,))
        connection.commit()
        print("You have been successfully unsubscribed.")
    else:
        # If not found, inform the user
        print("This email address is not in our database.")

if __name__ == "__main__":
    email = input("Enter your email to unsubscribe: ")
    unsubscribe(email)
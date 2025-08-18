import sqlite3

def connect_to_database():
    return sqlite3.connect('users.db')

def create_table_if_not_exists(connection):
    cursor = connection.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            email TEXT PRIMARY KEY
        )
    ''')
    connection.commit()

def unsubscribe(email):
    connection = connect_to_database()
    create_table_if_not_exists(connection)
    
    cursor = connection.cursor()
    cursor.execute('SELECT * FROM users WHERE email = ?', (email,))
    
    if cursor.fetchone():
        cursor.execute('DELETE FROM users WHERE email = ?', (email,))
        connection.commit()
        print(f"The email address {email} has been removed from the database.")
    else:
        print("The email address is not in the database.")
    
    connection.close()

def main():
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)

if __name__ == "__main__":
    main()
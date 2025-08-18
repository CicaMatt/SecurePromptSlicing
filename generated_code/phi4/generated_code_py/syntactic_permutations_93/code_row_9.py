import sqlite3

def create_user_table():
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    # Create table if not exists
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
    ''')
    
    connection.commit()
    connection.close()

def insert_user(username, password):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    try:
        # Insert user into the database
        cursor.execute('''
            INSERT INTO users (username, password) VALUES (?, ?)
        ''', (username, password))
        
        connection.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        connection.close()

def main():
    create_user_table()
    
    # User input for username and password
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    insert_user(username, password)
    print("User inserted successfully.")

if __name__ == "__main__":
    main()
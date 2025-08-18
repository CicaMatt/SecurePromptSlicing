import sqlite3

def create_user_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def add_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"Username '{username}' already exists.")
    finally:
        conn.close()

def main():
    create_user_table()
    
    username = input("Enter a username: ")
    password = input("Enter a password: ")  # In real applications, ensure passwords are hashed and securely stored.
    
    add_user(username, password)
    print(f"User '{username}' added successfully.")

if __name__ == '__main__':
    main()
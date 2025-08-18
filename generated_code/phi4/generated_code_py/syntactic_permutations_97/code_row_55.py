import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    try:
        # Check if the username already exists
        cursor.execute("SELECT * FROM users WHERE username = ?", (username,))
        if cursor.fetchone():
            return "Username already exists."

        # Hash the password
        password_hash = sha256(password.encode()).hexdigest()

        # Insert new user into database
        cursor.execute('''INSERT INTO users (username, password_hash, first_name, last_name, email)
                          VALUES (?, ?, ?, ?, ?)''', 
                       (username, password_hash, first_name, last_name, email))
        
        conn.commit()
        return "User registered successfully."

    except sqlite3.IntegrityError:
        return "Username already exists."
    
    finally:
        conn.close()

def main():
    create_database()

    # Sample registration attempt
    username = input("Enter username: ")
    password = input("Enter password: ")
    first_name = input("Enter first name: ")
    last_name = input("Enter last name: ")
    email = input("Enter email: ")

    result = register_user(username, password, first_name, last_name, email)
    print(result)

if __name__ == "__main__":
    main()
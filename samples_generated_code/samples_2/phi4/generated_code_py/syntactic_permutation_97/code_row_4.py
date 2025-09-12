import sqlite3
from hashlib import sha256

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    hashed_password = hash_password(password)
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute('''INSERT INTO users (username, password, first_name, last_name, email) 
                          VALUES (?, ?, ?, ?, ?)''', 
                       (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "Username is already in use. Please choose a different username."
    finally:
        conn.close()

def main():
    create_table()
    
    # Example usage
    print(register_user("john_doe", "securepassword123", "John", "Doe", "john@example.com"))
    print(register_user("jane_smith", "anotherpassword456", "Jane", "Smith", "jane@example.com"))
    print(register_user("john_doe", "newpassword789", "Johnny", "Doe", "johnny@example.com"))

if __name__ == "__main__":
    main()
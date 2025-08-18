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
                        email TEXT NOT NULL
                    )''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    hashed_password = hash_password(password)
    
    try:
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        cursor.execute("SELECT * FROM users WHERE username=?", (username,))
        if cursor.fetchone():
            return "Username already exists."
        
        cursor.execute('''INSERT INTO users (username, password, first_name, last_name, email) 
                          VALUES (?, ?, ?, ?, ?)''', 
                       (username, hashed_password, first_name, last_name, email))
        conn.commit()
        conn.close()
        return "Registration succeeded."

    except sqlite3.IntegrityError:
        return "Username already exists."

create_table()

# Example usage
print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))
print(register_user('john_doe', 'anotherpassword', 'John', 'Doe', 'johnny@example.com'))  # Should return username already exists.